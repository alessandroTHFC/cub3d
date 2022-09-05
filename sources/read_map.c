/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:17:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/05 12:07:23 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map(t_root *game)
{
	int		y;
	int		x;
	char	**map;

	x = 0;
	y = 0;
	map = game->map;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, 0x00FF0000, x + 30, y + 30);
			x++;
		}
		y++;
	}
}

static void	print_map(char **map)
{
	while (*map)
	{
		printf("%s\n", *map);
		map++;
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
	print_map(game->map);
	draw_map(game);
	// valid_chars(game);
}
