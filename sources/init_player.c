/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/08 10:48:31 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_orientation(char dir, int *x, int *y)
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

void	init_player(t_root *game, int x, int y, char dir)
{
	static t_player	me;

	me.tile_x = x;
	me.tile_y = y;
	me.x[0] = 15 + x;
	me.y[0] = 15 + y;
	me.rad = 0;
	init_orientation(dir, &me.x[1], &me.y[1]);
	me.x[1] += x;
	me.y[1] += y;
	game->me = &me;
	draw_line(game->mlx->minmap, me.x, me.y, 0x00FF0000);
}

int	x_rot(int x[2], int y[2], double radian)
{
	return (x[0] + ((x[1] - x[0]) * cos(radian) - (y[1] - y[0]) * sin(radian)));
}

int	y_rot(int x[2], int y[2], double radian)
{
	return (y[0] + ((x[1] - x[0]) * sin(radian) + (y[1] - y[0]) * cos(radian)));
}

void	rot_player(t_root *game)
{
	int	x;
	int	y;

	game->me->rad += 5;
	x = x_rot(game->me->x, game->me->y, game->me->rad * 0.01745);
	y = y_rot(game->me->x, game->me->y, game->me->rad * 0.01745);
	game->me->x[1] = x;
	game->me->y[1] = y;
	draw_line(game->mlx->minmap, game->me->x, game->me->y, 0x00FF0000);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minmap->img, 0, 0);
}
