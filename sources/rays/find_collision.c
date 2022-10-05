/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/06 10:23:52 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_index(t_root *game, char c, int i, int j)
{
	if (c == 'N' || c == 'S')
		i -= (TILE + 1) * (game->map[j][0]);
	else
		i -= (TILE + 1) * (game->map[0][j]);
	printf("index of square: %i\n", i);
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
		return (2);
	if (north == '1' && west == '0' && east == '1')
		return (4);
	if ((north == '1' && west == '1') || (north == '1' && west == '0'))
		return (1);
	return (3);
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
	count = 0;
	// if (game->me->rangle == -0.000000000000004139700734984153)
	// 	printf("N: %c S: %c E: %c W: %c\n", north, south, east, west);
	if ((north == '1' && south == '0'))
		count = 1;
	else if (north == '0' && south == '1' && west == '0')
		count = 2;
	else if (east == '1' && west == '0')
		count = 3;
	else
		count = 4;
	if ((north == '1' && south == '0' && east == '1' && west == '0')
		|| (north == '0' && south == '1' && east == '0' && west == '1'))
	{
		count = corner_collide(game, x, y);
	}
	if (!((y + 1) % (TILE + 1)) && !((x + 1) % (TILE + 1)))
		return (-20);
	if (count > 2)
		return (20);
	return (0);
}
