/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:53 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/07 10:44:27 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_root *game)
{
	int	x[2];
	int	y[2];
	int	i;

	draw_line(game->mlx->minmap, float_to_int(game->me->x, game->me->xt),
		float_to_int(game->me->y, game->me->yt), 0xABCDEFAB);
	x[0] = game->me->x[0] - 3;
	x[1] = x[0] + 5;
	y[0] = game->me->y[0] - 3;
	y[1] = y[0];
	i = 0;
	while (i < 5)
	{
		draw_line(game->mlx->minmap, x, y, 0xABCDEFAB);
		i++;
		y[0]++;
		y[1]++;
	}
}

void	update_player(t_root *game)
{
	game->me->tile_x = (int)(game->me->x[0] / (TILE + 1));
	game->me->tile_y = (int)(game->me->y[0] / (TILE + 1));
	draw_background(game, 0x009913e6, 0x00f7d8f9);
	if (game->map_toggle)
	{
		clear_map(game);
	}
	set_ray_angle(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->proj->img, 0, 0);
	if (game->map_toggle)
	{
		draw_player(game);
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->mlx->minmap->img, 0,
			1080 - ((game->map_height + 4) * (TILE + 1)));
	}
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
	game->me->angle = atan2(game->me->y[1] - game->me->y[0],
			game->me->x[1] - game->me->x[0]);
	update_player(game);
}

void	move_player(t_root *game, int dir)
{
	int		dx;
	int		dy;

	dx = ((game->me->x[1] - game->me->x[0]) * dir) * 20;
	dy = ((game->me->y[1] - game->me->y[0]) * dir) * 20;
	if (!check_collision(game, dx / 20 + game->me->x[0], dy / 20 + game->me->y[0]))
	{
		return ;
	}
	game->me->x[0] += dx / 20;
	game->me->x[1] += dx / 20;
	game->me->y[0] += dy / 20;
	game->me->y[1] += dy / 20;
	update_player(game);
}

/*	Functional, a little bit wiggly. */

void	strafe_player(t_root *game, int dir)
{
	double	x;
	double	y;
	double	strafe;

	strafe = game->me->angle - M_PI / 2;
	if (strafe < 0)
		strafe += M_PI * 2;
	if (strafe > M_PI * 2)
		strafe -= M_PI * 2;
	x = cos(strafe) * dir;
	y = sin(strafe) * dir;
	if (!check_collision(game, x + game->me->x[0], y + game->me->y[0]))
	{
		return ;
	}
	game->me->x[0] += x;
	game->me->x[1] += x;
	game->me->y[0] += y;
	game->me->y[1] += y;
	update_player(game);
}
