/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/13 16:39:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_index(t_root *game, int x, int y, int dir)
{
	int	i;

	if (dir < 2)
		i = x - (x / (TILE + 1)) * (TILE + 1);
	else
		i = y - (y / (TILE + 1)) * (TILE + 1);
	if ((dir % 2))
		i = TILE - i;
	game->me->text_i = i;
	game->index = dir;
}

int	corner_collide(t_root *game, int x, int y)
{
	int	north;
	int	south;
	int	east;
	int	west;

	north = game->map[(y - 1) / (TILE + 1)][x / (TILE + 1)];
	south = game->map[(y + 1) / (TILE + 1)][x / (TILE + 1)];
	east = game->map[(y + 1) / (TILE + 1)][(x + 1) / (TILE + 1)];
	west = game->map[(y + 1) / (TILE + 1)][(x - 1) / (TILE + 1)];
	if ((east == '1' && west == '1') || (north == '0' && west == '0'))
		return (1);
	if (north == '1' && west == '0' && east == '1')
		return (3);
	if ((north == '1' && west == '1') || (north == '1' && west == '0'))
		return (0);
	return (2);
}

int	find_side(t_root *game, int x, int y)
{
	int	count;
	int	north;
	int	south;
	int	east;
	int	west;

	north = game->map[(y - 1) / (TILE + 1)][x / (TILE + 1)];
	south = game->map[(y + 1) / (TILE + 1)][x / (TILE + 1)];
	east = game->map[y / (TILE + 1)][(x + 1) / (TILE + 1)];
	west = game->map[y / (TILE + 1)][(x - 1) / (TILE + 1)];
	if ((north == '1' && south == '0'))
		count = 0;
	else if (north == '0' && south == '1' && west == '0')
		count = 1;
	else if (east == '1' && west == '0')
		count = 2;
	else
		count = 3;
	if ((north == '1' && south == '0' && east == '1' && west == '0')
		|| (north == '0' && south == '1' && east == '0' && west == '1'))
		count = corner_collide(game, x, y);
	set_index(game, x, y, count);
	if (count > 1)
		return (-1);
	return (0);
}
