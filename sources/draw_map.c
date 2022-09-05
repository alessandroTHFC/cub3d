/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:32:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/05 11:57:47 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int colour)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->pixel_bits / 8));
	*(unsigned int *)dst = colour;
}

void	draw_square(t_root *game, int colour, int x_offset, int y_offset)
{
	int	x_coor[2];
	int	y_coor[2];

	x_coor[0] = x_offset;
	x_coor[1] = x_offset;
	y_coor[0] = y_offset;
	y_coor[1] = y_offset + 30;
	draw_line(game->mlx, x_coor, y_coor, colour);
	x_coor[0] = x_offset + 30;
	x_coor[1] = x_offset + 30;
	draw_line(game->mlx, x_coor, y_coor, colour);
	y_coor[0] = y_offset + 30;
	x_coor[1] = x_offset;
	draw_line(game->mlx, x_coor, y_coor, colour);
	y_coor[0] = y_offset;
	y_coor[1] = y_offset;
	draw_line(game->mlx, x_coor, y_coor, colour);
}
