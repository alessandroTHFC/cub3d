/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:23:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/05 10:09:43 by jbrown           ###   ########.fr       */
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

void	gentle_slope(t_mlx *mlx, int *x, int *y, int colour)
{
	int	dx;
	int	dy;
	int	d;
	int	x_curr;
	int	y_curr;

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	if (dy < 0)
		dy = -dy;
	d = (2 * dy) - dx;
	y_curr = y[0];
	x_curr = x[0];
	while (x_curr != x[1])
	{
		draw_pixel(mlx, x_curr, y_curr, colour);
		if (d > 0)
		{
			up_or_down(&y_curr, y[1]);
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		up_or_down(&x_curr, x[1]);
	}
	draw_pixel(mlx, x_curr, y_curr, colour);
}

void	steep_slope(t_mlx *mlx, int *x, int *y, int colour)
{
	int	dx;
	int	dy;
	int	d;
	int	x_curr;
	int	y_curr;

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	if (dx < 0)
		dx = -dx;
	d = (2 * dx) - dy;
	x_curr = x[0];
	y_curr = y[0];
	while (y_curr != y[1])
	{
		draw_pixel(mlx, x_curr, y_curr, colour);
		if (d > 0)
		{
			up_or_down(&x_curr, x[1]);
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		up_or_down(&y_curr, y[1]);
	}
	draw_pixel(mlx, x_curr, y_curr, colour);
}

void	draw_line(t_mlx *mlx, int *x, int *y, int colour)
{
	if (ft_abs(y[1] - y[0]) < ft_abs(x[1] - x[0]))
	{
		if (x[0] > x[1])
			gentle_slope(mlx, x, y, colour);
		else
			gentle_slope(mlx, x, y, colour);
	}
	else
	{
		if (y[0] > y[1])
			steep_slope(mlx, x, y, colour);
		else
			steep_slope(mlx, x, y, colour);
	}
}