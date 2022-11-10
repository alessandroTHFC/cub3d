/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:06:13 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/10 14:45:48 by jbrown           ###   ########.fr       */
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
	if (tx < 0 || tx > 44 || ty < 0 || ty > 13)
	{
		printf("No!\n");
	}
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
	{
		draw_line(game->mlx->minmap, x, y, colour);
	}
}

float	dist(float ax, float ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
