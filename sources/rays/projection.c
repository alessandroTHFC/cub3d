/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/10 15:41:01 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_square(double d)
{
	return (d * d);
}

void	draw_cursor(t_root *game)
{
	int	x[2];
	int	y[2];

	x[0] = game->win_width / 2 - 10;
	x[1] = x[0] + 19;
	y[0] = game->win_height / 2;
	y[1] = y[0];
	draw_line(game->proj, x, y, 0xFF000000);
	x[0] += 10;
	x[1] -= 9;
	y[0] -= 10;
	y[1] += 9;
	draw_line(game->proj, x, y, 0xFF000000);
}

int	add_shade(int colour, int side, int height)
{
	int	red;
	int	green;
	int	blue;

	(void)height;
	if (side == 0)
		return (colour);
	red = (0xFA & (colour >> 16));
	green = (0xFA & (colour >> 8));
	blue = (0xFA & colour);
	colour = (red << 16) + (green << 8) + blue;
	return (colour);
}

void	draw_wall(t_root *game, int x, int y, int side)
{
	int		y_end;
	int		x_y[2];
	float	i;
	int		x_err;
	float	step;

	x_y[0] = x;
	x_y[1] = 0;
	y_end = game->win_height - y;
	step = game->texts[game->i]->h / (float)(y_end - y);
	i = 0;
	x_err = (game->me->text_i * game->texts[game->i]->w) / (TILE);
	x_err *= game->texts[game->i]->img.pixel_bits / 8;
	if (y < 0)
	{
		i = step * -y;
		y = 0;
		// printf("%i\n", y);
	}
	// while (y < 0)
	// {
	// 	y++;
	// 	i += step;
	// }
	while (x_y[1] < game->win_height - 1)
	{
		if (x_y[1] >= y && x_y[1] < y_end)
		{
			// draw_pixel(game->proj, x_y, add_shade(0xFF00FF, side, y));
			draw_pixel(game->proj, x_y,
				add_shade(*(int *)(game->texts[game->i]->img.addr
						+ ((int)i * game->texts[game->i]->img.line_len
							+ x_err)), side, y));
			i += step;
		}
		else if (x_y[1] < game->win_height / 2)
			draw_pixel(game->proj, x_y, game->colours[0]);
		else
			draw_pixel(game->proj, x_y, game->colours[1]);
		x_y[1]++;
	}
	(void)side;
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	double		distance;
	int			height;
	int			side;

	side = find_side(game, end[0], end[1]);
	distance = dist(game->me->x[0], game->me->y[0], end[0], end[1]);
	if (game->fish_toggle)
		distance *= cos(game->me->rangle);
	height = 550 - ((TILE * 50) / (distance)) * 10;
	draw_wall(game, scan, height, side);
	scan += 1;
	if (scan == game->win_width)
	{
		draw_cursor(game);
		scan = 0;
	}
}
