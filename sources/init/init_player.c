/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/03 16:13:12 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Sets the initial player orientation to the correct direction.	*/

void	init_orientation(char dir, double x[2], double y[2])
{
	*x = TILE / 2;
	*y = TILE / 2;
	if (dir == 'N')
		*y = 0;
	if (dir == 'E')
		*x = TILE;
	if (dir == 'S')
		*y = TILE;
	if (dir == 'W')
		*x = 0;
}

/*	Sets initial values for player, including position on map and player
	angle.	*/

void	init_player(t_root *game, int x, int y, char *dir)
{
	static t_player	me;

	x /= game->tile;
	x *= TILE;
	y /= game->tile;
	y *= TILE;
	printf("x: %i, y: %i\n", x, y);
	me.tile_x = x;
	me.tile_y = y;
	me.x[0] = TILE / 2 + me.tile_x;
	me.y[0] = TILE / 2 + me.tile_y;
	me.rad = 5 * M_PI / 180;
	init_orientation(*dir, &me.x[1], &me.y[1]);
	*dir = '0';
	me.x[1] += me.tile_x;
	me.y[1] += me.tile_y;
	me.angle = atan2(me.y[1] - me.y[0], me.x[1] - me.x[0]);
	game->me = &me;
}
