/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:33:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/21 09:00:08 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *strs[4] = {
	"./textures/colours.xpm",
	"./textures/happy.xpm",
	"./textures/tex.xpm",
	"./textures/floral.xpm"
};

void	test(t_root *game)
{
	int				i;
	t_textures		*tmp;
	t_textures		**tex;

	tex = malloc(sizeof(*tex) * 4);
	i = 0;
	while (i < 4)
	{
		tmp = malloc(sizeof(*tmp));
		tmp->img.img = mlx_xpm_file_to_image(game->mlx->mlx,
				strs[i], &tmp->w, &tmp->h);
		tex[i] = tmp;
		tex[i]->addr = mlx_get_data_addr(tex[i]->img.img,
				&tex[i]->img.pixel_bits, &tex[i]->img.line_len,
				&tex[i]->img.endian);
		printf("h: %i, w: %i\n", tex[i]->w, tex[i]->h);
		i++;
	}
	game->texts = tex;
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
	width *= (TILE);
	height *= (TILE);
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
