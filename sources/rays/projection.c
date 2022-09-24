/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/24 15:39:18 by jbrown           ###   ########.fr       */
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

	x[0] = 1920 / 2 - 10;
	x[1] = x[0] + 19;
	y[0] = 1080 / 2;
	y[1] = y[0];
	draw_line(game->proj, x, y, 0xFF000000);
	x[0] += 10;
	x[1] -= 9;
	y[0] -= 10;
	y[1] += 9;
	draw_line(game->proj, x, y, 0xFF000000);
}

void	draw_wall(t_root *game, int x, int y, int colour)
{
	int	x_end[2];
	int	y_end[2];

	x_end[0] = x;
	x_end[1] = x;
	y_end[0] = y;
	y_end[1] = 1080 - y;
	draw_line(game->proj, x_end, y_end, colour);
}

int	create_trgb(int t, int r, int g, int b)
{
	if (g > 200)
		g = 200;
	return (t << 24 | r << 16 | g << 8 | b);
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	double		dist;
	int			height;

	dist = sqrt(ft_square(game->me->x[0] - end[0])
			+ ft_square(game->me->y[0] - end[1]));
	height = 500 - ((TILE * 50) / (dist)) * 10;
	if (height < 0)
		height = 0;
	draw_wall(game, scan, height, create_trgb(0, 255, dist, 255));
	scan += 1;
	if (scan == 1921)
	{
		draw_cursor(game);
		scan = 0;
	}
}