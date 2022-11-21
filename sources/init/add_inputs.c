/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:45:00 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/21 10:21:37 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_texture(t_root *game, int dir, char *file, int i)
{
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
	printf("PATH: [%s]\n", sub);
	game->paths[dir] = sub;
	return (j);
}

int	error_exit(char *msg, char *file)
{
	free(file);
	printf("%s\n", msg);
	return (1);
}

int	skip_white_space(char *file, int i)
{
	while (!ft_isspace(file[i]))
		i++;
	while (ft_isspace(file[i]))
		i++;
	return (i);
}

int	add_colour(t_root *game, int type, char *file, int i)
{
	int	colour;
	int	tmp;
	int	count;

	colour = 0;
	i = skip_white_space(file, i);
	count = -1;
	while (++count < 3)
	{
		tmp = ft_atoi(&file[i]);
		while (ft_isdigit(file[i]))
			i++;
		if ((tmp < 0 || tmp > 255)
			|| ((file[i] != ',' && count <= 2) && file[i] != '\n'))
			exit(error_exit("\e[31m\e[1mError\nInvalid Colour!\e[0m", file));
		colour = (colour << 8) + tmp;
		while (count < 2 && (ft_isspace(file[i]) || file[i] == ','))
			i++;
	}
	if (file[i] != '\n')
		exit(error_exit("\e[31m\e[1mError\nInvalid Colour!\e[0m", file));
	game->colours[type] = colour;
	while (file[i] != '\n')
		i++;
	return (i);
}
