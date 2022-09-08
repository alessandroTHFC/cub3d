/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:23:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/08 09:43:14 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	up_or_down(int *current, int end)
{
	if (end < *current)
		*current -= 1;
	else if (end > *current)
		*current += 1;
}

void	gentle_slope(t_img *img, int *x, int *y, int colour)
{
	int	dx;
	int	dy;
	int	d;
	int	x_y[2];

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	if (dy < 0)
		dy = -dy;
	d = (2 * dy) - dx;
	x_y[0] = x[0];
	x_y[1] = y[0];
	while (x_y[0] != x[1])
	{
		draw_pixel(img, x_y, colour);
		if (d > 0)
		{
			up_or_down(&x_y[1], y[1]);
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		up_or_down(&x_y[0], x[1]);
	}
	draw_pixel(img, x_y, colour);
}

void	steep_slope(t_img *img, int *x, int *y, int colour)
{
	int	dx;
	int	dy;
	int	d;
	int	x_y[2];

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	if (dx < 0)
		dx = -dx;
	d = (2 * dx) - dy;
	x_y[0] = x[0];
	x_y[1] = y[0];
	while (x_y[1] != y[1])
	{
		draw_pixel(img, x_y, colour);
		if (d > 0)
		{
			up_or_down(&x_y[0], x[1]);
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		up_or_down(&x_y[1], y[1]);
	}
	draw_pixel(img, x_y, colour);
}

void	draw_line(t_img *img, int *x, int *y, int colour)
{
	if (ft_abs(y[1] - y[0]) < ft_abs(x[1] - x[0]))
	{
		if (x[0] > x[1])
			gentle_slope(img, x, y, colour);
		else
			gentle_slope(img, x, y, colour);
	}
	else
	{
		if (y[0] > y[1])
			steep_slope(img, x, y, colour);
		else
			steep_slope(img, x, y, colour);
	}
}
