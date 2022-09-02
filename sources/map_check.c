/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:17:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 13:58:52 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*buffer_map(int fd)
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

void	import_map(char *map_loc, t_mlx *mlx)
{
	int		fd;
	int		i;
	char	*file;

	fd = open(map_loc, O_RDONLY);
	file = buffer_map(fd);
	mlx->map = ft_split(file, '\n');
	free (file);
	close (fd);
	i = 0;
	while (mlx->map[i])
	{
		printf("%s\n", mlx->map[i]);
		free(mlx->map[i]);
		i++;
	}
	free(mlx->map);
}
