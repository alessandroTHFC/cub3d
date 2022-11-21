/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_layers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:58:33 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/14 15:00:19 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_layer(t_root *game, t_img *img)
{
	int	x_y[2];

	x_y[1] = 0;
	while (x_y[1] < game->win_height)
	{
		x_y[0] = 0;
		while (x_y[0] < game->win_width)
		{
			draw_pixel(img, x_y, 0);
			x_y[0]++;
		}
		x_y[0] = 0;
		x_y[1]++;
	}
}

void	draw_layer(t_root *game, t_img *img)
{
	int	colour;
	int	x_y[2];
	int	x_add;

	x_add = img->pixel_bits / 8;
	x_y[1] = 0;
	while (x_y[1] < game->win_height)
	{
		x_y[0] = 0;
		while (x_y[0] < game->win_width)
		{
			colour = *(int *)(img->addr + ((int)x_y[1]
						* img->line_len + x_y[0] * x_add));
			if (colour)
			{
				draw_pixel(game->proj, x_y, colour);
			}
			x_y[0]++;
		}
		x_y[0] = 0;
		x_y[1]++;
	}
}
