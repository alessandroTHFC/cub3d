/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 12:06:27 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_loop(t_root *game, t_dda dda, int i)
{
	while (game->map[dda.x_y[1] / TILE][dda.x_y[0] / TILE] != '1' && i++ < 50)
	{
		dda.dx = dist(dda.x_y[0], dda.x_y[1], dda.v_check[0], dda.v_check[1]);
		dda.dy = dist(dda.x_y[0], dda.x_y[1], dda.h_check[0], dda.h_check[1]);
		if (dda.dy < dda.dx)
		{
			dda.x_y[0] = dda.h_check[0];
			dda.x_y[1] = dda.h_check[1];
			if (game->map[dda.h_check[1] / TILE][dda.h_check[0] / TILE] == '1')
				break ;
			dda.h_check[0] += dda.h_step[0];
			dda.h_check[1] += dda.h_step[1];
		}
		else
		{
			dda.x_y[0] = dda.v_check[0];
			dda.x_y[1] = dda.v_check[1];
			if (game->map[dda.v_check[1] / TILE][dda.v_check[0] / TILE] == '1')
				break ;
			dda.v_check[0] += dda.v_step[0];
			dda.v_check[1] += dda.v_step[1];
		}
	}
	normalise_ray(game, dda.x_y, 0xFF00FF);
	find_projection(game, dda.x_y);
}

void	edge_case(t_root *game, t_dda dda, float angle)
{
	if (angle == M_PI || !angle)
	{
		dda.v_check[0] = dda.x_y[0];
		dda.v_check[1] = dda.x_y[1];
		dda.h_check[0] = dda.x_y[0];
		dda.h_check[1] = dda.x_y[1];
		dda.h_step[1] = TILE;
		dda.h_step[0] = 0;
		dda.v_step[0] = TILE;
		dda.v_step[1] = 0;
	}
	dda.dx = dist(dda.x_y[0], dda.x_y[1], dda.v_check[0], dda.v_check[1]);
	dda.dy = dist(dda.x_y[0], dda.x_y[1], dda.h_check[0], dda.h_check[1]);
	if (dda.dx > dda.dy)
	{
		dda.x_y[0] = dda.h_check[0];
		dda.x_y[1] = dda.h_check[1];
	}
	else
	{
		dda.x_y[0] = dda.v_check[0];
		dda.x_y[1] = dda.v_check[1];
	}
	ray_loop(game, dda, 0);
}

void	set_step(t_root *game, t_dda dda, float angle)
{
	if (angle > M_PI)
	{
		dda.h_check[1] -= 1;
		dda.h_step[1] = -TILE;
	}
	if (angle < M_PI)
	{
		dda.h_check[1] += TILE;
		dda.h_step[1] = TILE;
	}
	dda.h_check[0] = (dda.x_y[1] - dda.h_check[1]) * dda.a_tan + dda.x_y[0];
	dda.h_step[0] = -dda.h_step[1] * dda.a_tan;
	if (angle > (M_PI / 2) && angle < (3 * M_PI / 2))
	{
		dda.v_check[0] -= 1;
		dda.v_step[0] = -TILE;
	}
	if (angle < (M_PI / 2) || angle > (3 * M_PI / 2))
	{
		dda.v_check[0] += TILE;
		dda.v_step[0] = TILE;
	}
	dda.v_check[1] = (dda.x_y[0] - dda.v_check[0]) * dda.n_tan + dda.x_y[1];
	dda.v_step[1] = -dda.v_step[0] * dda.n_tan;
	edge_case(game, dda, angle);
}

void	init_ray(t_root *game)
{
	t_dda	dda;
	float	angle;

	angle = game->me->rangle + game->me->angle;
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	dda.a_tan = -1 / tan(angle);
	dda.n_tan = -tan(angle);
	dda.x_y[0] = game->me->x[0];
	dda.x_y[1] = game->me->y[0];
	dda.h_check[1] = (dda.x_y[1] / TILE) * TILE;
	dda.v_check[0] = (dda.x_y[0] / TILE) * TILE;
	set_step(game, dda, angle);
}

void	set_ray_angle(t_root *game)
{
	int		x[2];
	int		y[2];
	int		i;
	double	rad;

	x[0] = game->me->x[0];
	x[1] = game->me->x[1];
	y[0] = game->me->y[0];
	y[1] = game->me->y[1];
	i = 0;
	rad = (-game->fov / 2) * (M_PI / 180);
	while (i < game->win_width)
	{
		game->me->rangle = rad;
		init_ray(game);
		rad += (game->fov * (M_PI / 180)) / game->win_width;
		i++;
		x[1] = game->me->x[1];
		y[1] = game->me->y[1];
	}
}
