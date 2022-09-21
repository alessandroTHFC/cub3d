/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/19 17:41:35 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_square(double d)
{
	return (d * d);
}

void	clear_projection(t_root *game)
{
	int	x;
	int	y;
	int	x_y[2];

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			x_y[0] = x;
			x_y[1] = y;
			draw_pixel(game->proj, x_y, 0x00000000);
			x++;
		}
		y++;
	}
	draw_map(game, false);
}

void	draw_wall(t_root *game, int x, int y, int colour)
{
	int	x_end[2];
	int	y_end[2];
	int	i;

	i = y;
	x_end[0] = x;
	x_end[1] = x + 100;
	y_end[0] = y;
	y_end[1] = y;
	while (y_end[0] < 1080 - y)
	{
		draw_line(game->proj, x_end, y_end, colour);
		y_end[0]++;
		y_end[1]++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	double		dist;
	int			height;
	double		angle;

	angle = atan2(end[1] - game->me->y[0], end[0] - game->me->x[0]);
	dist = sqrt(ft_square(ft_abs(game->me->x[0] - end[0]))
			+ ft_square(ft_abs(game->me->y[0] - end[1])));
	dist *= cos(angle);
	if (dist < 0)
		dist *= -1;
	printf("dist: %f\n", dist);
	height = 500 - ((TILE * 50) / (dist)) * 10;
	if (height < 0)
		height = 0;
	draw_wall(game, scan, height, create_trgb(0, 3 * dist + 50, 0, 255));
	scan += 21;
	if (scan == 21 * 90)
		scan = 0;
	(void)scan;
}
