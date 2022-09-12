/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:23:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/12 15:38:29 by jbrown           ###   ########.fr       */
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

int	direction(int curr, int dst)
{
	if (curr < dst)
		return (++curr);
	if (curr > dst)
		return (--curr);
	return (curr);
}

static void	bresenham(t_img *img, t_slope *s, bool dec, int colour)
{
	int	x_y[2];

	s->m = 2 * s->dy - s->dx;
	while ((s->x0 != s->x1 || s->y0 != s->y1))
	{
		s->x0 = direction(s->x0, s->x1);
		if (dec)
		{
			x_y[0] = s->y0;
			x_y[1] = s->x0;
		}
		else
		{
			x_y[1] = s->y0;
			x_y[0] = s->x0;
		}
		draw_pixel(img, x_y, colour);
		if (s->m < 0)
			s->m = s->m + 2 * s->dy;
		else
		{
			s->y0 = direction(s->y0, s->y1);
			s->m = s->m + 2 * s->dy - 2 * s->dx;
		}
	}
}

void	draw_line(t_img *img, int *x, int *y, int colour)
{
	t_slope	s;

	s.x0 = x[0];
	s.x1 = x[1];
	s.y0 = y[0];
	s.y1 = y[1];
	s.dx = ft_abs(s.x1 - s.x0);
	s.dy = ft_abs(s.y1 - s.y0);
	if (s.dy >= s.dx)
	{
		ft_swap(&s.y0, &s.x0);
		ft_swap(&s.y1, &s.x1);
		ft_swap(&s.dx, &s.dy);
		bresenham(img, &s, true, colour);
	}
	else
		bresenham(img, &s, false, colour);
}
