/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/23 16:06:36 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	x /= (TILE + 1);
	y /= (TILE + 1);
	if (map[y][x] == '1')
		return (true);
	return (false);
}

static void	bresenham(t_root *game, t_slope *s, bool dec, int colour)
{
	int	x_y[2];
	int	x_dir;
	int	y_dir;

	if (s->x0 < s->x1)
		x_dir = 1;
	else
		x_dir = -1;
	if (s->y0 < s->y1)
		y_dir = 1;
	else
		y_dir = -1;
	s->m = 2 * s->dy - s->dx;
	while (1)
	{
		s->x0 += x_dir;
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
		draw_pixel(game->mlx->minmap, x_y, colour);
		if (is_wall(game->map, x_y[0], x_y[1]))
			break ;
		if (s->m < 0)
			s->m = s->m + 2 * s->dy;
		else
		{
			s->y0 += y_dir;
			s->m = s->m + 2 * s->dy - 2 * s->dx;
		}
	}
	// printf("x1: %i\ny1: %i\n", x_y[0], x_y[1]);
	find_projection(game, x_y);
}

void	draw_ray(t_root *game, double *x, double *y, int colour)
{
	t_slope		s;
	static int	xl;
	static int	yl;

	s.x0 = (int)x[0];
	s.x1 = (int)x[1];
	s.y0 = (int)y[0];
	s.y1 = (int)y[1];
	s.dx = ft_abs(s.x1 - s.x0);
	s.dy = ft_abs(s.y1 - s.y0);
	if (xl && yl)
		printf("x1: %i\ny1: %i\n", xl, yl);
	if (xl && xl == s.x1 && yl && yl == s.y1)
	{
		s.x1--;
		s.y1--;
	}
	xl = s.x1;
	yl = s.y1;
	printf("x1: %i\ny1: %i\n", xl, yl);
	if (s.dy >= s.dx)
	{
		ft_swap(&s.y0, &s.x0);
		ft_swap(&s.y1, &s.x1);
		ft_swap(&s.dx, &s.dy);
		bresenham(game, &s, true, colour);
	}
	else
		bresenham(game, &s, false, colour);
}

void	increment_angle(t_root *game, double x[2], double y[2], double r)
{
	double	xt;
	double	yt;

	game->me->col_x = x[1];
	game->me->col_y = y[1];
	xt = x[1];
	yt = y[1];
	xt -= x[0];
	yt -= y[0];
	x[1] = ((xt * cos(r)) - (yt * sin(r)));
	y[1] = ((xt * sin(r)) + (yt * cos(r)));
	x[1] += x[0];
	y[1] += y[0];
	draw_ray(game, x, y, 0xFFFF00);
}

void	set_ray_angle(t_root *game)
{
	double	x[2];
	double	y[2];
	int		i;
	int		count;

	x[0] = game->me->x[0];
	x[1] = game->me->x[1];
	y[0] = game->me->y[0];
	y[1] = game->me->y[1];
	i = -(FOV / 2);
	count = 0;
	while (i < FOV / 2)
	{
		game->me->ray_angle = i * D_RAD;
		increment_angle(game, x, y, game->me->ray_angle);
		i += 1;
		x[1] = game->me->x[1];
		y[1] = game->me->y[1];
		count++;
	}
}
