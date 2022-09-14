/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:53 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/14 21:19:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Converts a float array[2] to an int array[2] to be used in the pixel put
	function.	*/

int	*float_to_int(double fval[2], int ival[2])
{
	ival[0] = (int)fval[0];
	ival[1] = (int)fval[1];
	return (ival);
}

void	update_player(t_root *game)
{
	clear_map(game);
	draw_line(game->mlx->minmap, float_to_int(game->me->x, game->me->xt),
		float_to_int(game->me->y, game->me->yt), 0xABCDEFAB);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minmap->img, 0, 0);
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
	update_player(game);
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
	update_player(game);
}

/*	Functional, a little bit wiggly. */

void	strafe_player(t_root *game, int dir)
{
	double	x;
	double	y;
	double	strafe;

	strafe = atan2(game->me->y[1] - game->me->y[0],
			game->me->x[1] - game->me->x[0]) - M_PI / 2;
	if (strafe < 0)
		strafe += M_PI * 2;
	if (strafe > M_PI * 2)
		strafe -= M_PI * 2;
	x = cos(strafe) * dir;
	y = sin(strafe) * dir;
	game->me->x[0] += x;
	game->me->x[1] += x;
	game->me->y[0] += y;
	game->me->y[1] += y;
	update_player(game);
}
