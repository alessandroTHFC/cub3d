/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:33:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/19 17:26:02 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_image(t_mlx *mlx)
{
	static t_img	img;

	img.img = mlx_new_image(mlx->mlx, 800, 1080);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	mlx->minmap = &img;
}

static void	init_mlx(t_root *game)
{
	static t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "cub3d");
	get_image(&mlx);
	game->mlx = &mlx;
}

static void	init_projection(t_root *game)
{
	static t_img	img;

	img.img = mlx_new_image(game->mlx->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	game->proj = &img;
}

void	init_root(t_root *game)
{
	init_mlx(game);
	init_projection(game);
	draw_map(game, true);
	update_player(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minmap->img, 0, 700);
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 17, 0, clean_exit, game);
	mlx_loop(game->mlx->mlx);
}
