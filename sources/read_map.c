/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:17:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/12 12:49:59 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_mlx *mlx, int x, int y, int colour)
{
	int	coor[2];

	coor[0] = x + 15;
	coor[1] = y + 15;
	draw_pixel(mlx->minmap, coor, colour);
	(void) mlx;
	(void) colour;
}

static void	draw_map(t_root *game)
{
	static int		y;
	static int		x;
	static int		x_offset;
	static int		y_offset;
	char			**map;

	map = game->map;
	while (map[y])
	{
		x = 0;
		x_offset = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, 0x00FF0000, x + x_offset, y + y_offset);
			if (map[y][x] == '0')
				draw_square(game, 0x000000FF, x + x_offset, y + y_offset);
			if (ft_strchr("NESW", map[y][x]))
				init_player(game, x + x_offset, y + y_offset, map[y][x]);
			x++;
			x_offset += 30;
		}
		y++;
		y_offset += 30;
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

	fd = open(map_loc, O_RDONLY);
	file = buffer_map(fd);
	game->map = ft_splice(file, '\n', game);
	error_checker(game);
	free (file);
	close (fd);
	print_map(game->map);
	draw_map(game);
}
