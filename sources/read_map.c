/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:17:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 12:58:59 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_width(t_root *game)
{
	int	i;
	int	curr;
	int	biggest;

	i = 0;
	biggest = ft_strlen(game->map[i]);
	while (game->map[i])
	{
		curr = ft_strlen(game->map[i]);
		if (curr > biggest)
			biggest = curr;
		i++;
	}
	game->map_width = biggest;
}

void	draw_circle(t_mlx *mlx, int x, int y, int colour)
{
	int	coor[2];

	coor[0] = x + 15;
	coor[1] = y + 15;
	draw_pixel(mlx->minmap, coor, colour);
	(void) mlx;
	(void) colour;
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
	file[bytes_read] = 0;
	while (bytes_read)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
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
	char	*map;

	fd = open(map_loc, O_RDONLY);
	file = buffer_map(fd);
	map = file;
	map = get_textures(game, file);
	game->map = ft_splice(map, '\n', game);
	set_width(game);
	error_checker(game);
	free (file);
	close (fd);
	print_map(game->map);
}
