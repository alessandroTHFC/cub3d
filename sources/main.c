/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:45:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/21 10:30:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

///Function gets length of map file name - 4 places and compares
///final four characters if they match .cub 
///if yes, game continues, if no game exits.
void	check_filetype(char *map_file)
{
	size_t	i;

	i = strlen(map_file) - 4;
	if (!ft_memcmp(&map_file[i], ".cub", 4))
		return ;
	printf("\e[31m\e[1mError\nInvalid Map File \e[0m \n");
	exit(1);
}

int	main(int argc, char **argv)
{
	t_root	game;

	if (argc != 2)
	{
		printf("Incorrect Inputs!");
		return (1);
	}
	check_filetype(argv[1]);
	import_map(argv[1], &game);
	init_root(&game);
	return (0);
}
