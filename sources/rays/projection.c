/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/19 15:35:48 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_square(double d)
{
	return (d * d);
}

void	draw_wall(t_root *game, int x, int y, int colour)
{
	int	x_end[2];
	int	y_end[2];
	int	i;

	x_end[0] = x;
	x_end[1] = x + 100;
	y_end[0] = y;
	y_end[1] = y;
	i = 0;
	while (y_end[0] < 1080 - y)
	{
		draw_line(game->mlx->minmap, x_end, y_end, colour);
		y_end[0]++;
		y_end[1]++;
	}
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	int			dist;
	int			height;

	// printf("x0 %i, y0 %i\n", (int)game->me->x[0], (int)game->me->x[1]);
	// printf("x1 %i, y0 %i\n", end[0], end[1]);
	dist = sqrt(ft_square(ft_abs(game->me->x[0] - end[0]))
			+ ft_square(ft_abs(game->me->y[0] - end[1])));
	printf("distance: %i\n", dist);
	height = 500 - ((TILE * 50) / (dist)) * 10;
	if (height < 0)
		height = 0;
	draw_wall(game, scan, height, 0xFFA500);
	scan += 10;
	if (scan == 900)
		scan = 0;
	printf("height: %i\n", height);
	(void)scan;
}
