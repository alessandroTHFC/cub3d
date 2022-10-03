/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:25:05 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/24 13:32:00 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_root *game, int floor, int ceiling)
{
	int	x[2];
	int	y[2];

	x[0] = 0;
	x[1] = 1920;
	y[0] = 0;
	y[1] = 0;
	while (y[0] <= 1080 / 2)
	{
		draw_line(game->proj, x, y, ceiling);
		y[0]++;
		y[1]++;
	}
	while (y[0] <= 1080)
	{
		draw_line(game->proj, x, y, floor);
		y[0]++;
		y[1]++;
	}
}
