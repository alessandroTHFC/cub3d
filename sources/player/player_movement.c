/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:53 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/14 14:58:50 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_root *game)
{
	int	x[2];
	int	y[2];
	int	i;

	x[0] = (game->me->x[0] / TILE) * game->tile;
	x[1] = (game->me->x[1] / TILE) * game->tile;
	y[0] = (game->me->y[0] / TILE) * game->tile;
	y[1] = (game->me->y[1] / TILE) * game->tile;
	draw_line(game->mlx->minmap, x, y, 0xCDEFAB);
	x[0] -= 3;
	x[1] = x[0] + 5;
	y[0] -= 3;
	y[1] = y[0];
	i = 0;
	while (i < 5)
	{
		draw_line(game->mlx->minmap, x, y, 0xCDEFAB);
		i++;
		y[0]++;
		y[1]++;
	}
}

void	update_player(t_root *game)
{
	game->me->tile_x = (int)(game->me->x[0] / (TILE));
	game->me->tile_y = (int)(game->me->y[0] / (TILE));
	set_ray_angle(game);
	if (game->map_toggle)
	{
		draw_map(game, false);
		draw_player(game);
		draw_layer(game, game->mlx->minmap);
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->proj->img, 0, 0);
}

/*	Rotates the player on button press.	*/

void	rot_player(t_root *game, int dir)
{
	game->me->angle += (dir * (M_PI / 180));
	if (game->me->angle < 0)
		game->me->angle += 2 * M_PI;
	if (game->me->angle > 2 * M_PI)
		game->me->angle -= 2 * M_PI;
	game->me->x[1] = game->me->x[0] + cos(game->me->angle) * (TILE / 2) + 5;
	game->me->y[1] = game->me->y[0] + sin(game->me->angle) * (TILE / 2) + 5;
}

void	move_player(t_root *game, int dir)
{
	double	x;
	double	y;

	x = game->me->x[0] + cos(game->me->angle) * (dir * TILE / 4);
	y = game->me->y[0] + sin(game->me->angle) * (dir * TILE / 4);
	if (check_collision(game, x, game->me->y[0]))
	{
		game->me->x[0] = x;
	}
	if (check_collision(game, game->me->x[0], y))
	{
		game->me->y[0] = y;
	}
	game->me->x[1] = game->me->x[0] + cos(game->me->angle) * (TILE / 4) + 5;
	game->me->y[1] = game->me->y[0] + sin(game->me->angle) * (TILE / 4) + 5;
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
	x = game->me->x[0] + cos(strafe) * (dir * TILE / 8);
	y = game->me->y[0] + sin(strafe) * (dir * TILE / 8);
	if (check_collision(game, x, game->me->y[0]))
	{
		game->me->x[0] = x;
	}
	if (check_collision(game, game->me->x[0], y))
	{
		game->me->y[0] = y;
	}
	game->me->x[1] = game->me->x[0] + cos(game->me->angle) * (TILE / 2) + 5;
	game->me->y[1] = game->me->y[0] + sin(game->me->angle) * (TILE / 2) + 5;
}
