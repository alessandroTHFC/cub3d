/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:40:18 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/14 15:00:08 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggles(int key, t_root *game)
{
	if (key == FTOGGLE)
		game->fish_toggle = !game->fish_toggle;
	if (key == MTOGGLE)
		game->map_toggle = !game->map_toggle;
	if (key == FOVUP && game->fov < 2000)
		game->fov += 100;
	if (key == FOVDOWN && game->fov > 500)
		game->fov -= 100;
	update_player(game);
}

int	key_press(int key, t_root *game)
{
	key = (short)key + OFFSET;
	printf("key pressed: %i\n", key);
	if (key == EXIT)
		clean_exit(game);
	if (key == FTOGGLE || key == MTOGGLE || key == FOVUP || key == FOVDOWN)
	{
		toggles(key, game);
		return (1);
	}
	game->key_pressed[key] = true;
	return (0);
}

int	key_release(int key, t_root *game)
{
	key = (short)key + OFFSET;
	if (key == FTOGGLE || key == MTOGGLE)
	{
		return (1);
	}
	game->key_pressed[key] = false;
	return (0);
}

static bool	key_b(t_root *game, int key)
{
	return (game->key_pressed[key]);
}

int	game_hook(t_root *game)
{
	static int	y;
	static int	x;

	if (x != game->win_width / 2 && x)
	{
		mlx_mouse_move(game->mlx->win, game->win_width / 2,
			game->win_height / 2);
		rot_player(game, x - game->win_width / 2);
	}
	mlx_mouse_get_pos(game->mlx->win, &x, &y);
	mlx_mouse_hide();
	if (key_b(game, LEFT))
		rot_player(game, -10);
	if (key_b(game, RIGHT))
		rot_player(game, 10);
	if (key_b(game, UP) || key_b(game, W))
		move_player(game, 1);
	if (key_b(game, DOWN) || key_b(game, S))
		move_player(game, -1);
	if (key_b(game, A))
		strafe_player(game, -1);
	if (key_b(game, D))
		strafe_player(game, 1);
	update_player(game);
	return (0);
}
