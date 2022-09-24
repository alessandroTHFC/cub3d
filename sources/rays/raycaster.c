/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/24 15:43:51 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	int	tx;
	int	ty;

	tx = x + 1;
	ty = y + 1;
	tx /= (TILE + 1);
	ty /= (TILE + 1);
	x /= (TILE + 1);
	y /= (TILE + 1);
	if (map[y][x] == '1' || map[ty][tx] == '1'
			|| map[y][tx] == '1' || map[ty][x] == '1')
		return (true);
	return (false);
}

static void	bresenham(t_root *game, t_slope *s, bool dec, int colour)
{
	int	x_y[2];
	int	x_dir;
	int	y_dir;

	x_dir = ray_direction(s->x0, s->x1);
	y_dir = ray_direction(s->y0, s->y1);
	s->m = 2 * s->dy - s->dx;
	while (1)
	{
		s->x0 += x_dir;
		ray_vector(x_y, s->x0, s->y0, dec);
		if (game->map_toggle)
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
	find_projection(game, x_y);
}

void	draw_ray(t_root *game, int *x, int *y, int colour)
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
		bresenham(game, &s, true, colour);
	}
	else
		bresenham(game, &s, false, colour);
}

void	increment_angle(t_root *game, int x[2], int y[2], double r)
{
	double	xt;
	double	yt;
	double	rad;

	rad = r;
	xt = (x[1] - x[0]) * 100;
	yt = (y[1] - y[0]) * 100;
	x[1] = ((xt * cos(rad)) - (yt * sin(rad)));
	y[1] = ((xt * sin(rad)) + (yt * cos(rad)));
	x[1] += x[0];
	y[1] += y[0];
	draw_ray(game, x, y, 0xFFFF00);
}

void	set_ray_angle(t_root *game)
{
	int		x[2];
	int		y[2];
	int		i;
	double	rad;

	x[0] = game->me->x[0];
	x[1] = game->me->x[1];
	y[0] = game->me->y[0];
	y[1] = game->me->y[1];
	i = 0;
	rad = (-FOV / 2) * (M_PI / 180);
	while (i <= 1920)
	{
		increment_angle(game, x, y, rad);
		rad += (M_PI / 180) / (FOV / 2);
		i += 1;
		x[1] = game->me->x[1];
		y[1] = game->me->y[1];
	}
}
