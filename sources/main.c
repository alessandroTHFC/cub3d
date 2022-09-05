/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:45:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/05 15:55:54 by jbrown           ###   ########.fr       */
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

<<<<<<< HEAD
void	get_image(t_mlx *mlx)
{
	t_img	img;

	img.img = mlx_new_image(mlx->mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	mlx->minmap = &img;
=======
void	check_filetype(char *map_file, t_root *game)
{
	size_t	i;

	i = strlen(map_file) - 4;
	if (!ft_memcmp(&map_file[i], ".cub", 4))
		return ;
	printf("\e[31m\e[1mError\nInvalid Map File \e[0m \n");
	clean_exit(game);
>>>>>>> a1900a3ccfc8b423a6715eabb8619fe72400f285
}

int	main(int argc, char **argv)
{
	t_root		game;
	t_mlx		mlx;
	t_img		img;
	///Need to initialise the struct values! (i.e player count to 0);
	if (argc != 2)
	{
		printf("Incorrect Inputs!");
		return (1);
	}
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "cub3d");
	img.img = mlx_new_image(mlx.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	mlx.minmap = &img;
	game.mlx = &mlx;
	check_filetype(argv[1], &game);
	//error_checker(&game);
	import_map(argv[1], &game);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.minmap->img, 0, 0);
	mlx_key_hook(mlx.win, key_press, &game);
	mlx_loop(mlx.mlx);
	return (0);
}
