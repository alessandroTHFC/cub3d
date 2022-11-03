/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/03 16:17:46 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(char **map, int x, int y)
{
	int	tx;
	int	ty;

	tx = x + 1;
	ty = y + 1;
	tx /= (TILE);
	ty /= (TILE);
	x /= (TILE);
	y /= (TILE);
	if (map[y][x] == '1' || map[ty][tx] == '1'
		|| map[y][tx] == '1' || map[ty][x] == '1')
		return (true);
	return (false);
}

void	normalise_ray(t_root *game, int x_y[2], int colour)
{
	int	x[2];
	int	y[2];

	x[0] = game->me->x[0] * game->tile / TILE;
	x[1] = x_y[0] * game->tile / TILE;
	y[0] = game->me->y[0] * game->tile / TILE;
	y[1] = x_y[1] * game->tile / TILE;
	if (game->map_toggle)
		draw_line(game->mlx->minmap, x, y, colour);
}

float	dist(float ax, float ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	more_ray(t_root *game)
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
	//init
	dda.h_check[1] = (dda.x_y[1] / TILE) * TILE;
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
	dda.v_check[0] = (dda.x_y[0] / TILE) * TILE;
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
	//set steps
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
	//set distance
	int	i	= 0;
	while (game->map[dda.x_y[1] / TILE][dda.x_y[0] / TILE] != '1')
	{
		dda.dx = dist(dda.x_y[0], dda.x_y[1], dda.v_check[0], dda.v_check[1]);
		dda.dy = dist(dda.x_y[0], dda.x_y[1], dda.h_check[0], dda.h_check[1]);
		if (dda.dy < dda.dx)
		{
			dda.x_y[0] = dda.h_check[0];
			dda.x_y[1] = dda.h_check[1];
			if (game->map[dda.h_check[1] / TILE][dda.h_check[0] / TILE] == '1')
			{
				break ;
			}
			dda.h_check[0] += dda.h_step[0];
			dda.h_check[1] += dda.h_step[1];
		}
		else
		{
			dda.x_y[0] = dda.v_check[0];
			dda.x_y[1] = dda.v_check[1];
			if (game->map[dda.v_check[1] / TILE][dda.v_check[0] / TILE] == '1')
			{
				break ;
			}
			dda.v_check[0] += dda.v_step[0];
			dda.v_check[1] += dda.v_step[1];
		}
		i++;
		if (i > 50)
			break ;
	}
	//calculate
	normalise_ray(game, dda.x_y, 0xFF00FF);
	find_projection(game, dda.x_y);
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
		more_ray(game);
		rad += (game->fov * (M_PI / 180)) / game->win_width;
		i++;
		x[1] = game->me->x[1];
		y[1] = game->me->y[1];
	}
}
