/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:40:18 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/10 16:15:56 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggles(int key, t_root *game)
{
	if (key == FTOGGLE)
		game->fish_toggle = !game->fish_toggle;
	if (key == MTOGGLE)
		game->map_toggle = !game->map_toggle;
	if (key == FOVUP && game->fov < 90)
		game->fov += 10;
	if (key == FOVDOWN && game->fov > 40)
		game->fov -= 10;
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

int	mouse_move(int move, t_root *game)
{
	printf("%i\n", move);
	if (move < 960)
	{
		printf("Going left\n");
		// game->key_pressed[LEFT] = true;
		// game->key_pressed[RIGHT] = false;
	}
	else
	{
		printf("Going right\n");
		// game->key_pressed[LEFT] = false;
		// game->key_pressed[RIGHT] = true;
	}
	// printf("%i\n", game->win_height);
	(void)game;
	return (0);
}

static bool	key_b(t_root *game, int key)
{
	return (game->key_pressed[key]);
}

int	game_hook(t_root *game)
{
	int	dir;
	static int	x, y;

	mlx_mouse_get_pos(game->mlx->win, &x, &y);
	printf("%i, %i\n", x, y);
	if (key_b(game, LEFT) || key_b(game, S)
		|| key_b(game, D) || key_b(game, DOWN))
			dir = -1;
	if (key_b(game, RIGHT) || key_b(game, W)
		|| key_b(game, A) || key_b(game, UP))
			dir = 1;
	if (key_b(game, LEFT) || key_b(game, RIGHT))
		rot_player(game, dir);
	if (key_b(game, W) || key_b(game, S)
		|| key_b(game, UP) || key_b(game, DOWN))
		move_player(game, dir);
	if (key_b(game, A) || key_b(game, D))
		strafe_player(game, dir);
		rot_player(game, x - game->win_width / 2);
	
	mlx_mouse_move(game->mlx->win, game->win_width / 2, game->win_height / 2);
	return (0);
}
