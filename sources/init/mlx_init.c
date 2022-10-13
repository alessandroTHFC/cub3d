/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:33:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/13 17:28:46 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test(t_root *game)
{
	int				w;
	int				h;
	static t_img	wall;
	static char		*wall_pointer;
	t_textures		*tex;

	tex = malloc(sizeof(*tex) * 4);
	wall.img = mlx_xpm_file_to_image(game->mlx->mlx, "./textures/colours.xpm", &tex[0].w, &tex[0].h);
	tex[0].img = &wall;
	wall.img = mlx_xpm_file_to_image(game->mlx->mlx, "./textures/colours.xpm", &tex[1].w, &tex[1].h);
	tex[1].img = &wall;
	wall.img = mlx_xpm_file_to_image(game->mlx->mlx, "./textures/colours.xpm", &tex[2].w, &tex[2].h);
	tex[2].img = &wall;
	wall.img = mlx_xpm_file_to_image(game->mlx->mlx, "./textures/colours.xpm", &tex[3].w, &tex[3].h);
	tex[3].img = &wall;
	tex[0].img->img = mlx_xpm_file_to_image(game->mlx->mlx, "./textures/text.xpm", &tex[0].w, &tex[0].h);
	tex[0].addr = mlx_get_data_addr(tex[0].img->img, &tex[0].img->pixel_bits, &tex[0].img->line_len, &tex[0].img->endian);
	tex[1].addr = mlx_get_data_addr(tex[1].img->img, &tex[1].img->pixel_bits, &tex[1].img->line_len, &tex[1].img->endian);
	tex[2].addr = mlx_get_data_addr(tex[2].img->img, &tex[2].img->pixel_bits, &tex[2].img->line_len, &tex[2].img->endian);
	tex[3].addr = mlx_get_data_addr(tex[3].img->img, &tex[3].img->pixel_bits, &tex[3].img->line_len, &tex[3].img->endian);
	wall.img = mlx_xpm_file_to_image(game->mlx->mlx, "./textures/colours.xpm", &w, &h);
	wall_pointer = mlx_get_data_addr(wall.img, &wall.pixel_bits, &wall.line_len, &wall.endian);
	game->wall = &wall;
	game->tex_h = h;
	game->tex_w = w;
	game->wall_pointer = wall_pointer;
	game->texts = &tex;
}

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
	int				width;
	int				height;

	width = game->map_width + 4;
	height = game->map_height + 1;
	width *= (TILE + 1);
	height *= (TILE + 1);
	img.img = mlx_new_image(game->mlx->mlx, width, 1080);
	img.addr = mlx_get_data_addr(img.img,
			&img.pixel_bits,
			&img.line_len, &img.endian);
	game->mlx->minmap = &img;
}

static void	init_mlx(t_root *game)
{
	static t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "cub3d");
	game->mlx = &mlx;
	get_image(game);
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
	game->map_toggle = false;
	game->fish_toggle = true;
	set_false(game);
	init_mlx(game);
	test(game);
	init_projection(game);
	draw_map(game, true);
	update_player(game);
	mlx_do_key_autorepeatoff(game->mlx->mlx);
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	// mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx->win, 17, 0, clean_exit, game);
	mlx_loop_hook(game->mlx->mlx, game_hook, game);
	mlx_loop(game->mlx->mlx);
}
