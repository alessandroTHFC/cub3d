/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:45:00 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 11:47:25 by jbrown           ###   ########.fr       */
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

int	add_colour(t_root *game, int type, char *file, int i)
{
	int	colour;

	while (!ft_isspace(file[i]))
		i++;
	while (ft_isspace(file[i]))
		i++;
	colour = ft_atoi(&file[i]);
	while (ft_isdigit(file[i]))
		i++;
	while (ft_isspace(file[i]) || file[i] == ',')
		i++;
	colour = (colour << 8) + ft_atoi(&file[i]);
	while (ft_isdigit(file[i]))
		i++;
	while (ft_isspace(file[i]) || file[i] == ',')
		i++;
	colour = (colour << 8) + ft_atoi(&file[i]);
	printf("PATH: [%x]\n", colour);
	game->colours[type] = colour;
	while (ft_isdigit(file[i]))
		i++;
	while (file[i] != '\n')
		i++;
	return (i);
}
