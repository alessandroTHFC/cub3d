/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:25:05 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/03 13:57:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_root *game, int floor, int ceiling)
{
	int	x[2];
	int	y[2];

	x[0] = 0;
	x[1] = game->win_width;
	y[0] = 0;
	y[1] = 0;
	while (y[0] <= game->win_height / 2)
	{
		draw_line(game->proj, x, y, ceiling);
		y[0]++;
		y[1]++;
	}
	while (y[0] < game->win_height - 1)
	{
		draw_line(game->proj, x, y, floor);
		y[0]++;
		y[1]++;
	}
}
