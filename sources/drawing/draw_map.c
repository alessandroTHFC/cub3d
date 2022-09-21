/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:32:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/19 17:00:38 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_map(t_root *game)
{
	int	x;
	int	y;
	int	x_y[2];

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			x_y[0] = x;
			x_y[1] = y;
			draw_pixel(game->mlx->minmap, x_y, 0x00000000);
			x++;
		}
		y++;
	}
	draw_map(game, false);
}

void	draw_map(t_root *game, bool init)
{
	int		y;
	int		x;
	int		x_offset;
	int		y_offset;
	char	**map;

	y = -1;
	y_offset = 0;
	map = game->map;
	while (map[++y])
	{
		x = -1;
		x_offset = 0;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				draw_square(game, 0x00FF0000, x + x_offset, y + y_offset);
			if (init && ft_strchr("NESW", map[y][x]))
				init_player(game, x + x_offset, y + y_offset, &map[y][x]);
			if (map[y][x] == '0')
				draw_square(game, 0x000000FF, x + x_offset, y + y_offset);
			x_offset += TILE;
		}
		y_offset += TILE;
	}
}

void	draw_pixel(t_img *img, int *x_y, int colour)
{
	char	*dst;

	dst = img->addr
		+ (x_y[1] * img->line_len + x_y[0]
			* (img->pixel_bits / 8));
	*(unsigned int *)dst = colour;
}

void	draw_square(t_root *game, int colour, int x_offset, int y_offset)
{
	int	x_coor[2];
	int	y_coor[2];
	int	i;

	y_coor[0] = y_offset;
	y_coor[1] = y_offset;
	x_coor[0] = x_offset;
	x_coor[1] = x_offset + TILE;
	i = 0;
	while (i < TILE)
	{
		draw_line(game->mlx->minmap, x_coor, y_coor, colour);
		y_coor[0]++;
		y_coor[1]++;
		i++;
	}

	// x_coor[0] = x_offset;
	// x_coor[1] = x_offset;
	// y_coor[0] = y_offset;
	// y_coor[1] = y_offset + TILE;
	// draw_line(game->mlx->minmap, x_coor, y_coor, colour);
	// x_coor[0] = x_offset + TILE;
	// x_coor[1] = x_offset + TILE;
	// draw_line(game->mlx->minmap, x_coor, y_coor, colour);
	// y_coor[0] = y_offset + TILE;
	// x_coor[1] = x_offset;
	// draw_line(game->mlx->minmap, x_coor, y_coor, colour);
	// y_coor[0] = y_offset;
	// y_coor[1] = y_offset;
	// draw_line(game->mlx->minmap, x_coor, y_coor, colour);
}
