/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:32:41 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 16:02:04 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int colour)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->pixel_bits / 8));
	*(unsigned int *)dst = colour;
}

void	draw_square(t_root *game, int colour)
{
	int	x;
	int	y;

	x = 10;
	y = 10;
	while (++x < 50)
	{
		draw_pixel(game->mlx, x, y, colour);
	}
	x = 10;
	y = 50;
	while (++x < 50)
	{
		draw_pixel(game->mlx, x, y, colour);
	}
	while (--y > 10)
	{
		draw_pixel(game->mlx, x, y, colour);
	}
	x = 10;
	y = 10;
	while (++y < 50)
	{
		draw_pixel(game->mlx, x, y, colour);
	}
}
