/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:45:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/05 12:20:49 by jbrown           ###   ########.fr       */
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

void	check_filetype(char *map_file, t_root *game)
{
	size_t	i;

	i = strlen(map_file) - 4;
	if (!ft_memcmp(&map_file[i], ".cub", 4))
		return ;
	printf("\e[31m\e[1mError\nInvalid Map File \e[0m \n");
	clean_exit(game);
}

int	main(int argc, char **argv)
{
	t_root		game;
	t_mlx		mlx;
	///Need to initialise the struct values! (i.e player count to 0);
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
	check_filetype(argv[1], &game);
	//error_checker(&game);
	import_map(argv[1], &game);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_press, &game);
	mlx_loop(mlx.mlx);
	return (0);
}
