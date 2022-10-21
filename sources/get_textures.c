/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:30:49 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/14 10:13:54 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_texture(t_root *game, int dir, char *file, int i)
{
	t_textures	*curr;
	char		*sub;
	int			j;

	while (!ft_isspace(file[i]))
		i++;
	while (ft_isspace(file[i]))
		i++;
	j = i;
	while (!ft_isspace(file[j]))
		j++;
	sub = ft_substr(file, i, j - i);
	printf("PATH: %s\n", sub);
	curr = malloc(sizeof(*curr));
	printf("0\n");
	curr->img.img = mlx_xpm_file_to_image(game->mlx->mlx,
		sub, &curr->w, &curr->h);
	printf("1\n");
	free(sub);
	curr->addr = mlx_get_data_addr(curr->img.img, &curr->img.pixel_bits,
		&curr->img.line_len, &curr->img.endian);
	game->texts[dir] = curr;
	return (j);
}

void	get_textures(t_root *game, char *file)
{
	int	i;
	int	count;
	t_textures		**tex;

	i = 0;
	count = 0;
	tex = malloc(sizeof(*tex) * 4);
	tex[0] = NULL;
	tex[1] = NULL;
	tex[2] = NULL;
	tex[3] = NULL;
	game->texts = tex;
	while (count < 4)
	{
		while (ft_isspace(file[i]))
			i++;
		if (ft_strncmp("NO ", &file[i], 3) && ft_strncmp("SO ", &file[i], 3)
			&& ft_strncmp("EA ", &file[i], 3) && ft_strncmp("WE ", &file[i], 3)
			&& ft_strncmp("F ", &file[i], 2) && ft_strncmp("C ", &file[i], 2))
		{
			printf("Invalid Inputs!\n");
			exit(1);
		}
		if (!strncmp("NO ", &file[i], 3) && !tex[0])
			i = add_texture(game, 0, file, i);
		if (!strncmp("SO ", &file[i], 3) && !tex[1])
			i = add_texture(game, 1, file, i);
		if (!strncmp("EA ", &file[i], 3) && !tex[2])
			i = add_texture(game, 2, file, i);
		if (!strncmp("WE ", &file[i], 3) && !tex[3])
			i = add_texture(game, 3, file, i);
		count++;
	}
}