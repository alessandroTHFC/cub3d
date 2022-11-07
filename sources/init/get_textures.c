/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:30:49 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 11:46:16 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_inputs(t_root *game)
{
	if (game->paths[0] && game->paths[1] && game->paths[2] && game->paths[3])
		return ;
	if (game->colours[0] != -1 && game->colours[1] != -1)
		return ;
	printf("Paths not entered correctly!\n");
}

void	init_paths(t_root *game)
{
	game->paths = malloc(sizeof(*game->paths) * 4);
	game->paths[0] = NULL;
	game->paths[1] = NULL;
	game->paths[2] = NULL;
	game->paths[3] = NULL;
	game->colours[0] = -1;
	game->colours[1] = -1;
}

int	path_check(t_root *game, char *file, int i)
{
	if (!strncmp("NO ", &file[i], 3) && !game->paths[0])
		i = add_texture(game, 0, file, i);
	else if (!strncmp("SO ", &file[i], 3) && !game->paths[1])
		i = add_texture(game, 1, file, i);
	else if (!strncmp("EA ", &file[i], 3) && !game->paths[2])
		i = add_texture(game, 2, file, i);
	else if (!strncmp("WE ", &file[i], 3) && !game->paths[3])
		i = add_texture(game, 3, file, i);
	else if (!strncmp("C ", &file[i], 2))
		i = add_colour(game, 0, file, i);
	else if (!strncmp("F ", &file[i], 2))
		i = add_colour(game, 1, file, i);
	else
		return (-1);
	return (i);
}

char	*get_textures(t_root *game, char *file)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	init_paths(game);
	while (count < 6)
	{
		while (ft_isspace(file[i]))
			i++;
		i = path_check(game, file, i);
		if (i < 0)
		{
			printf("Invalid Inputs!\n");
			exit(1);
		}
		count++;
	}
	check_inputs(game);
	return (&file[i]);
}
