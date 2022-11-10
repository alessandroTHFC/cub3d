/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:33:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/10 16:03:23 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_false(t_root *game)
{
	game->key_pressed[W] = false;
	game->key_pressed[A] = false;
	game->key_pressed[S] = false;
	game->key_pressed[D] = false;
	game->key_pressed[UP] = false;
	game->key_pressed[DOWN] = false;
	game->key_pressed[LEFT] = false;
	game->key_pressed[RIGHT] = false;
}

static void	get_image(t_root *game)
{
	static t_img	img;

	img.img = mlx_new_image(game->mlx->mlx, game->win_width, game->win_height);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	game->mlx->minmap = &img;
}

static void	init_mlx(t_root *game)
{
	static t_mlx	mlx;

	game->win_width = 1920;
	game->win_height = 1080;
	game->fov = FOV;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, game->win_width,
			game->win_height, "cub3d");
	game->mlx = &mlx;
	get_image(game);
}

static void	init_projection(t_root *game)
{
	static t_img	img;

	img.img = mlx_new_image(game->mlx->mlx, game->win_width, game->win_height);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	game->proj = &img;
}


void	init_root(t_root *game)
{
	game->map_toggle = false;
	game->fish_toggle = true;
	printf("mapx: %i\nmapy: %i\n", game->map_width, game->map_height);
	set_false(game);
	init_mlx(game);
	apply_textures(game);
	init_projection(game);
	draw_map(game, true);
	update_player(game);
	mlx_do_key_autorepeatoff(game->mlx->mlx);
	mlx_mouse_hook(game->mlx->win, mouse_move, game);
	// mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 17, 0, clean_exit, game);
	mlx_loop_hook(game->mlx->mlx, game_hook, game);
	mlx_loop(game->mlx->mlx);
}
