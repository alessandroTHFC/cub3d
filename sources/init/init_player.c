/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/02 15:03:34 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Sets the initial player orientation to the correct direction.	*/

void	init_orientation(char dir, double x[2], double y[2])
{
	*x = TILE;
	*y = TILE;
	if (dir == 'N')
		*y = 0;
	if (dir == 'E')
		*x = TILE * 2;
	if (dir == 'S')
		*y = TILE * 2;
	if (dir == 'W')
		*x = 0;
}

/*	Sets initial values for player, including position on map and player
	angle.	*/

void	init_player(t_root *game, int x, int y, char *dir)
{
	static t_player	me;

	me.tile_x = x;
	me.tile_y = y;
	me.x[0] = TILE + x;
	me.y[0] = TILE + y;
	me.rad = 5 * M_PI / 180;
	init_orientation(*dir, &me.x[1], &me.y[1]);
	*dir = '0';
	me.x[1] += x;
	me.y[1] += y;
	me.angle = atan2(me.y[1] - me.y[0], me.x[1] - me.x[0]);
	game->me = &me;
}
