/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:45:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 13:46:03 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_mlx *mlx)
{
	printf("%i\n", key);
	if (key == EXIT)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (key);
}

int	main(int argc, char **argv)
{
	t_root	game;
	t_mlx	mlx;

	game.mlx = &mlx;
	if (argc != 2)
	{
		printf("Incorrect Inputs!");
		return (1);
	}
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "cub3d");
	import_map(argv[1], &mlx);
	mlx_key_hook(mlx.win, key_press, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
