/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:50:36 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/17 12:18:14 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

///check_counting function uses strchr to compare the character at the x, y 
///grid position passed in to see if it matches the allowed chars in the game
///(1, space, 0, N, S, E, W), if no, cleanly exits the program.
///if all valid, checks if there is a NSEW which indicates a player
///increments the player count to later be checked for valid amount of players.
static int	check_count(t_root *game, int y, int x)
{
	if (!ft_strchr("1 0NSEWC", game->map[y][x]))
	{
		printf("\e[31m\e[1mError\nUnknown characters in the map!! \e[0m \n");
		printf("this char is invalid %c\n", game->map[y][x]);
		exit(1);
	}
	if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
			game->map[y][x] == 'W' || game->map[y][x] == 'E')
				game->player_count++;
	return (0);
}

///valid_chars function iterates over the 2d map array
///at each grid position calls the check and counting function
///once out of the loop and map has valid characters it checks
///if the player count is valid (only 1 player allowed).
static int	valid_chars(t_root *game)
{
	int	x;
	int	y;

	y = 0;
	game->player_count = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			check_count(game, y, x);
			x++;
		}
		y++;
	}
	if (game->player_count != 1)
	{
		printf("\e[31m\e[1mError\nGame components incorrect, ");
		printf("only 1 player allowed you jackass! \e[0m \n");
		return (1);
	}
	return (0);
}

void	error_checker(t_root *game)
{
	if (internal_spaces(game) || valid_chars(game)
		|| horizontal_edges(game) || end_string_validity(game))
		free_map(game->map);
}
