/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:17:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 14:48:55 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_count(t_root *game, int y, int x)
{
	if (!ft_strchr("1  0NSEWC", game->map[y][x]))
	{
		printf("\e[31m\e[1mError\nUnknown characters in the map!! \e[0m \n");
		printf("this char is invalid %c\n", game->map[y][x]);
	}
	if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
			game->map[y][x] == 'W' || game->map[y][x] == 'E')
				game->player_count++;
}

static void	valid_chars(t_root *game)
{
	int	x;
	int	y;

	y = 0;
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
		// free_exit(game);
	}
}

static char	*buffer_map(int fd)
{
	static char	*buffer;
	char		*file;
	char		*tmp;
	int			bytes_read;

	file = malloc(BUFFER_SIZE + 1);
	bytes_read = read(fd, file, BUFFER_SIZE);
	while (bytes_read)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		bytes_read = read(fd, file, BUFFER_SIZE);
		tmp = file;
		file = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	if (buffer)
		free(buffer);
	return (file);
}

void	import_map(char *map_loc, t_root *game)
{
	int		fd;
	char	*file;

	fd = open(map_loc, O_RDONLY);
	file = buffer_map(fd);
	game->map = ft_split(file, '\n');
	free (file);
	close (fd);
	valid_chars(game);
}
