/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:40:18 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/24 16:23:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_root *game)
{
	int	dir;

	if (key == LEFT || key == S || key == D || key == DOWN)
			dir = -1;
	if (key == RIGHT || key == W || key == A || key == UP)
			dir = 1;
	if (key == LEFT || key == RIGHT)
		rot_player(game, dir);
	if (key == W || key == S || key == UP || key == DOWN)
		move_player(game, dir);
	if (key == A || key == D)
		strafe_player(game, dir);
	if (key == MTOGGLE)
	{
		game->map_toggle = !game->map_toggle;
		update_player(game);
	}
	if (key == EXIT)
		clean_exit(game);
	return (key);
}

int	mouse_move(int move, t_root *game)
{
	printf("%i\n", move);
	if (move < 960)
	{
		printf("Going left\n");
		rot_player(game, -1);
	}
	else
	{
		printf("Going right\n");
		rot_player(game, 1);
	}
	return (move);
}
