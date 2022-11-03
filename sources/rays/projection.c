/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/03 15:36:00 by jbrown           ###   ########.fr       */
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
	red = (0xEF0000 & colour);
	green = (0xEF00 & colour);
	blue = (0xEF & colour);
	colour = red + green + blue;
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
	x_y[1] = y;
	y_end = game->win_height - y;
	step = game->texts[game->i]->h / (float)(y_end - y);
	i = 0;
	x_err = (game->me->text_i * game->texts[game->i]->w) / (TILE);
	x_err *= game->texts[game->i]->img.pixel_bits / 8;
	while (x_y[1] != y_end)
	{
		if (x_y[1] > 0 && x_y[1] < game->win_height)
			draw_pixel(game->proj, x_y,
				add_shade(*(int *)(game->texts[game->i]->addr
						+ ((int)i * game->texts[game->i]->img.line_len
							+ x_err)), side, y));
		i += step;
		x_y[1]++;
	}
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	double		dist;
	int			height;
	int			side;

	side = find_side(game, end[0], end[1]);
	dist = sqrt(ft_square(game->me->x[0] - end[0])
			+ ft_square(game->me->y[0] - end[1]));
	if (game->fish_toggle)
		dist *= cos(game->me->rangle);
	height = 550 - ((TILE * 50) / (dist)) * 10;
	draw_wall(game, scan, height, side);
	scan += 1;
	if (scan == game->win_width)
	{
		draw_cursor(game);
		scan = 0;
	}
}
