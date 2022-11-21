/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:51:24 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/02 21:49:43 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free (map[i]);
		i++;
	}
	free (map);
	exit(0);
}

int	clean_exit(t_root *game)
{
	mlx_destroy_image(game->mlx->mlx, game->mlx->minmap->img);
	mlx_destroy_image(game->mlx->mlx, game->proj->img);
	mlx_destroy_window(game->mlx->mlx, game->mlx->win);
	free_map(game->map);
	return (0);
}
