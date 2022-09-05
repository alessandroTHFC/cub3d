/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:17:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 16:05:01 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	valid_chars(game);
}
