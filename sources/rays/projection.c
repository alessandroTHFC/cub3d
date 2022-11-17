/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/17 14:02:58 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	set_wall_top(float *y, float *i, int step)
{
	if (*y < 0)
	{
		*i = (float)(step * -(*y));
		*y = 0;
	}
	else
		*i = 0;
}

int	draw_wall_segment(t_root *game, float i, int side, int y)
{
	int	colour;
	int	x_err;

	x_err = (game->me->text_i * game->texts[game->i]->w) / (TILE);
	x_err *= game->texts[game->i]->img.pixel_bits / 8;
	colour = add_shade(*(int *)(game->texts[game->i]->img.addr
				+ ((int)i * game->texts[game->i]->img.line_len + x_err)),
			side, y);
	return (colour);
}

void	draw_wall(t_root *game, int x, float y, int side)
{
	int		y_end;
	int		x_y[2];
	float	i;
	float	step;

	x_y[0] = x;
	x_y[1] = 0;
	y_end = game->win_height - y;
	step = game->texts[game->i]->h / (float)(y_end - y);
	set_wall_top(&y, &i, step);
	while (x_y[1] < game->win_height - 1)
	{
		if (x_y[1] >= y && x_y[1] < y_end)
		{
			draw_pixel(game->proj, x_y, draw_wall_segment(game, i, side, y));
			i += step;
		}
		else if (x_y[1] < game->win_height / 2)
			draw_pixel(game->proj, x_y, game->colours[0]);
		else
			draw_pixel(game->proj, x_y, game->colours[1]);
		x_y[1]++;
	}
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	double		distance;
	float		height;
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
