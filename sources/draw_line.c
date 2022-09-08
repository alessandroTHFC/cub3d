/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:23:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/08 17:32:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

static void	line_draw(t_img *img, t_deltas *dlt, int colour)
{
	int	i;

	i = -1;
	while ((dlt->x0 != dlt->x1 || dlt->y0 != dlt->y1) && ++i < 50)
	{
		dlt->x_y[0] = dlt->x0;
		dlt->x_y[1] = dlt->y1;
		draw_pixel(img, dlt->x_y, colour);
		dlt->error[1] = 2 * dlt->error[0];
		if (dlt->error[1] > dlt->dy)
		{
			dlt->error[0] += dlt->dy;
			dlt->x0 += dlt->sx;
		}
		if (dlt->error[1] < dlt->dx)
		{
			dlt->error[0] += dlt->dx;
			dlt->x0 += dlt->sx;
		}
	}
	printf("Line Drawn.\n");
}

void	find_steep(t_img *img, t_deltas *dlt, int colour)
{
	if (ft_abs(dlt->y1 - dlt->y0) > ft_abs(dlt->x1 - dlt->x0))
	{
		if (dlt->x0 <= dlt->x1)
		{
			ft_swap(&dlt->x0, &dlt->x1);
			ft_swap(&dlt->y0, &dlt->y1);
		}
	}
	else
	{
		ft_swap(&dlt->dx, &dlt->dy);
		if (dlt->y0 <= dlt->y1)
		{
			ft_swap(&dlt->x0, &dlt->x1);
			ft_swap(&dlt->y0, &dlt->y1);
		}
	}
	line_draw(img, dlt, colour);
}

void	draw_line(t_img *img, int *x, int *y, int colour)
{
	t_deltas	dlt;

	dlt.x0 = x[0];
	dlt.x1 = x[1];
	dlt.y0 = y[0];
	dlt.y1 = y[1];
	dlt.dx = ft_abs(dlt.x1 - dlt.x0);
	dlt.dy = ft_abs(dlt.y1 - dlt.y0);
	dlt.error[0] = dlt.dx + dlt.dy;
	dlt.x_y[0] = dlt.x0;
	dlt.x_y[1] = dlt.x1;
	if (dlt.x0 < dlt.x1)
		dlt.sx = 1;
	else
		dlt.sx = -1;
	if (dlt.y0 < dlt.y1)
		dlt.sy = 1;
	else
		dlt.sy = -1;
	find_steep(img, &dlt, colour);
}
