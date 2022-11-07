/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:32:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 11:48:56 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tile_size(t_root *game)
{
	int	x;
	int	y;

	x = game->win_width / game->map_width;
	y = game->win_height / game->map_height;
	if (x < y)
		game->tile = x - 10;
	else
		game->tile = y - 10;
}

void	draw_map(t_root *game, bool init)
{
	int		y;
	int		x;
	int		x_offset;
	int		y_offset;

	y = -1;
	y_offset = 0;
	tile_size(game);
	while (game->map[++y])
	{
		x = -1;
		x_offset = 0;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == '1')
				draw_square(game, 0x00FF0000, x + x_offset, y + y_offset);
			if (init && ft_strchr("NESW", game->map[y][x]))
				init_player(game, x + x_offset, y + y_offset, &game->map[y][x]);
			if (game->map[y][x] == '0')
				draw_square(game, 0x000000FF, x + x_offset, y + y_offset);
			x_offset += game->tile - 1;
		}
		y_offset += game->tile - 1;
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
	x_coor[1] = x_offset + game->tile - 1;
	i = 0;
	while (i < game->tile - 1)
	{
		draw_line(game->proj, x_coor, y_coor, colour);
		y_coor[0]++;
		y_coor[1]++;
		i++;
	}
}
