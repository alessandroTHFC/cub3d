/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/14 14:34:32 by jbrown           ###   ########.fr       */
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
		float_to_int(me.y, me.yt), 0x00FF0000);
}

/*	Rotates the player on button press.	*/

void	rot_player(t_root *game, int dir)
{
	double	x;
	double	y;
	double	rad;

	rad = game->me->rad * dir;
	x = game->me->x[1];
	y = game->me->y[1];
	x -= game->me->x[0];
	y -= game->me->y[0];
	game->me->x[1] = ((x * cos(rad)) - (y * sin(rad)));
	game->me->y[1] = ((x * sin(rad)) + (y * cos(rad)));
	game->me->x[1] += game->me->x[0];
	game->me->y[1] += game->me->y[0];
	clear_map(game);
	draw_line(game->mlx->minmap, float_to_int(game->me->x, game->me->xt),
		float_to_int(game->me->y, game->me->yt), 0x00FF0000);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minmap->img, 0, 0);
}

void	move_player(t_root *game, int dir)
{
	int		dx;
	int		dy;

	dx = (game->me->x[1] - game->me->x[0]) * dir;
	dy = (game->me->y[1] - game->me->y[0]) * dir;
	game->me->x[0] += dx / 2;
	game->me->x[1] += dx / 2;
	game->me->y[0] += dy / 2;
	game->me->y[1] += dy / 2;
	clear_map(game);
	draw_line(game->mlx->minmap, float_to_int(game->me->x, game->me->xt),
		float_to_int(game->me->y, game->me->yt), 0x00FF0000);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minmap->img, 0, 0);
}