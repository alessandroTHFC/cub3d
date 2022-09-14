/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/14 15:35:53 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Sets the initial player orientation to the correct direction.	*/

void	init_orientation(char dir, double x[2], double y[2])
{
	*x = 15;
	*y = 15;
	if (dir == 'N')
		*y = 0;
	if (dir == 'E')
		*x = 30;
	if (dir == 'S')
		*y = 30;
	if (dir == 'W')
		*x = 0;
}

/*	Converts a float array[2] to an int array[2] to be used in the pixel put
	function.	*/

int	*float_to_int(double fval[2], int ival[2])
{
	ival[0] = (int)fval[0];
	ival[1] = (int)fval[1];
	return (ival);
}

/*	Sets initial values for player, including position on map and player
	angle.	*/

void	init_player(t_root *game, int x, int y, char *dir)
{
	static t_player	me;

	me.tile_x = x;
	me.tile_y = y;
	me.x[0] = 15 + x;
	me.y[0] = 15 + y;
	me.rad = 30 * M_PI / 180;
	init_orientation(*dir, &me.x[1], &me.y[1]);
	*dir = '0';
	me.x[1] += x;
	me.y[1] += y;
	game->me = &me;
	draw_line(game->mlx->minmap, float_to_int(me.x, me.xt),
		float_to_int(me.y, me.yt), 0xABCDEFAB);
}
