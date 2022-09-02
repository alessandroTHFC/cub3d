/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:45:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 16:03:26 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_root *game)
{
	printf("%i\n", key);
	if (key == EXIT)
	{
		clean_exit(game);
	}
	return (key);
}

int	main(int argc, char **argv)
{
	t_root		game;
	t_mlx		mlx;

	if (argc != 2)
	{
		printf("Incorrect Inputs!");
		return (1);
	}
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "cub3d");
	mlx.img = mlx_new_image(mlx.mlx, 1920, 1080);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.pixel_bits,
			&mlx.line_len, &mlx.endian);
	game.mlx = &mlx;
	import_map(argv[1], &game);
	draw_square(&game, 0x00FF0000);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_press, &game);
	mlx_loop(mlx.mlx);
	return (0);
}
