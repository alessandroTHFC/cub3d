/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:43:27 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/19 09:34:20 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_proximity(t_root *game, double x, double y, int wall)
{
	int	x_map;
	int	y_map;

	if (wall == 1)
		y += TILE / 4;
	if (wall == -1)
		y -= TILE / 4;
	if (wall == 2)
		x += TILE / 4;
	if (wall == -2)
		x -= TILE / 4;
	x_map = (int)(x / (TILE + 1));
	y_map = (int)(y / (TILE + 1));
	if (game->map[y_map][x_map] == '1')
		return (false);
	return (true);
}

bool	check_collision(t_root *game, double x, double y)
{
	int	x_map;
	int	y_map;
	int	wall;

	x_map = (int)(x / (TILE + 1));
	y_map = (int)(y / (TILE + 1));
	if (game->map[y_map][x_map] == '1')
		return (false);
	wall = cardinal_space(game, y_map, x_map, '1');
	if (!wall)
		return (true);
	return (check_proximity(game, x, y, wall));
}
