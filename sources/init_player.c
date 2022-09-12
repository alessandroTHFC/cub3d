/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/12 15:43:07 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_orientation(char dir, float x[2], float y[2])
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

int	*float_to_int(float fval[2], int ival[2])
{
	ival[0] = (int)fval[0];
	ival[1] = (int)fval[1];
	return (ival);
}

void	init_player(t_root *game, int x, int y, char dir)
{
	static t_player	me;

	me.tile_x = x;
	me.tile_y = y;
	me.x[0] = 15 + x;
	me.y[0] = 15 + y;
	me.rad = 45 * M_PI / 180;
	init_orientation(dir, &me.x[1], &me.y[1]);
	me.x[1] += x;
	me.y[1] += y;
	game->me = &me;
	draw_line(game->mlx->minmap, float_to_int(me.x, me.xt),
		float_to_int(me.y, me.yt), 0x00FF0000);
}

void	rot_player(t_root *game)
{
	int		x;
	int		y;

	x = game->me->x[1];
	y = game->me->y[1];
	x -= game->me->x[0];
	y -= game->me->y[0];
	game->me->x[1] = (x * cos(game->me->rad)) - (y * sin(game->me->rad));
	game->me->y[1] = (x * sin(game->me->rad)) + (y * cos(game->me->rad));
	game->me->x[1] += game->me->x[0];
	game->me->y[1] += game->me->y[0];
	draw_line(game->mlx->minmap, float_to_int(game->me->x, game->me->xt),
		float_to_int(game->me->y, game->me->yt), 0x00FF0000);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minmap->img, 0, 0);
}
