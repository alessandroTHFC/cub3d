/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/16 21:07:37 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(t_root *game)
{
	int		x[2];
	int		y[2];
	int		r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo;

	ra = game->me->angle;
	for (r = 0;r < 1; r++)
	{
		dof = 0;
		float	aTan = -1 / tan(game->me->angle);
		if (ra > M_PI)
		{
			ry = game->me->y[0];
			rx = (game->me->y[0] - ry) * aTan + game->me->x[0];
			yo = -TILE;
			xo = -yo * aTan;
		}
		if (ra < M_PI)
		{
			ry = (game->me->y[0] + TILE);
			rx = (game->me->y[0] - ry) * aTan + game->me->x[0];
			yo = TILE;
			xo = -yo * aTan;
		}
		(void)xo;
		(void)dof;
		(void)mp;
		(void)my;
		(void)mx;
		// while (dof < 3)
		// {
		// 	mx = (int)(rx) / TILE;
		// 	my = (int)(ry) / TILE;
		// 	mp = my * game->map_width + mx;
		// 	if (mp < game->map_width * game->map_height && game->map[my][mx] == '1')
		// 		dof = 3;
		// 	else
		// 	{
		// 		rx += xo;
		// 		ry += yo;
		// 		dof += 1;
		// 	}
		// }
		x[0] = game->me->x[0];
		x[1] = rx;
		y[0] = game->me->y[0];
		y[1] = ry;
		draw_line(game->mlx->minmap, x, y, 0x000FFFFF);
	}
}
