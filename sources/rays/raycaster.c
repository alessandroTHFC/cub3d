/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/24 15:56:35 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	int	tx;
	int	ty;

	// printf("4\n");
	tx = x + 1;
	ty = y + 1;
	tx /= (TILE);
	ty /= (TILE);
	x /= (TILE);
	y /= (TILE);
	if (map[y][x] == '1' || map[ty][tx] == '1'
		|| map[y][tx] == '1' || map[ty][x] == '1')
		return (true);
	return (false);
}

void	normailse_ray(t_root *game, int x_y[2], int colour)
{
	int	x[2];
	int	y[2];

	if (x[1] < 0 || x[1] >= 1920)
		return ;
	x[0] = game->me->x[0] * TILE_DRAW / TILE;
	x[1] = x_y[0] * TILE_DRAW / TILE;
	y[0] = game->me->y[0] * TILE_DRAW / TILE;
	y[1] = x_y[1] * TILE_DRAW / TILE;
	// printf("x: %i\ny: %i\n", x_y[0], x_y[1]);
	draw_line(game->mlx->minmap, x, y, colour);
	// (void)colour;
}

void	ray_test(t_root *game, t_slope *s)
{
	// int		y_int;
	// int		x_other;
	float	curr_angle;
	// int	y_step;
	// int	x_step;
	int		x_y[2];
	int		tmpxy[2];
	int		i = 0;
	static int count;

	curr_angle = -(game->me->angle + game->me->rangle);
	// if (!(count % 10))
	// 	printf("angle: %i\n", (int)(curr_angle * (180 / M_PI)));
	tmpxy[1] = (s->y0 / TILE) * TILE;
	if (s->y0 > s->y1)
		tmpxy[1] -= 1;
	else
		tmpxy[1] += TILE;
	tmpxy[0] = s->x0 + (s->y0 - tmpxy[1]) / tan(curr_angle);
	printf("y check\nx: %i\ny: %i\n", tmpxy[0], tmpxy[1]);
	if (tmpxy[1] < 1400 && tmpxy[1] > 0 && tmpxy[0] < 2900 && tmpxy[0] > 0)
	{
		while (game->map[tmpxy[1] / TILE][tmpxy[0] / TILE] != '1' && i < 30)
		{
			x_y[0] = tmpxy[0];
			x_y[1] = tmpxy[1];
			tmpxy[0] += TILE / tan(curr_angle);
			if (s->y0 > s->y1)
				tmpxy[1] -= TILE;
			else
				tmpxy[1] += TILE;
			i++;
			if ((tmpxy[1] / TILE) < 0 || (tmpxy[1] / TILE) >= 1400
				|| (tmpxy[0] / TILE) < 0 || (tmpxy[0] / TILE) >= 2900)
				break ;
		}
		normailse_ray(game, x_y, 0xFF00FF);
	}
	tmpxy[0] = (s->x0 / TILE) * TILE;
	// printf("x: %i\n", s->x0 / TILE);
	if (s->x0 < s->x1)
		tmpxy[0] -= 1;
	else
		tmpxy[0] += TILE;
	tmpxy[1] = s->y0 + (s->x0 - tmpxy[0]) * tan(curr_angle);
	printf("x check\nx: %i\ny: %i\n", tmpxy[0], tmpxy[1]);
	if (tmpxy[1] < 1100 && tmpxy[1] > 0 && tmpxy[0] < 2900 && tmpxy[0] > 0)
	{
		i = 0;
		while (game->map[tmpxy[1] / TILE][tmpxy[0] / TILE] != '1' && i < 5)
		{
			x_y[0] = tmpxy[0];
			x_y[1] = tmpxy[1];
			tmpxy[1] += TILE * tan(curr_angle);
			if (s->x0 > s->x1)
				tmpxy[0] -= TILE;
			else
				tmpxy[0] += TILE;
			i++;
			if ((tmpxy[1] / TILE) < 0 || (tmpxy[1] / TILE) >= 1400
				|| (tmpxy[0] / TILE) < 0 || (tmpxy[0] / TILE) >= 2900)
				break ;
		}
		count++;
		// printf("x: %i\ny: %i\n", x_y[0] / TILE, x_y[1] / TILE);
		normailse_ray(game, x_y, 0xF0F0FF);
	}
}

static void	bresenham(t_root *game, t_slope *s, bool dec, int colour)
{
	int	x_y[2];
	int	x_dir;
	int	y_dir;
	int	x;

	x_dir = ray_direction(s->x0, s->x1);
	y_dir = ray_direction(s->y0, s->y1);
	x = s->x0;
	while (ft_abs(s->x0 - x) < (TILE) * 50)
	{
		s->x0 += x_dir;
		ray_vector(x_y, s->x0, s->y0, dec);
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
	// if (game->map_toggle)
	// 	normailse_ray(game, x_y, colour);
	find_projection(game, x_y);
	(void)colour;
}

void	draw_ray(t_root *game, int *x, int *y, int colour)
{
	t_slope	s;
	bool	dec;

	dec = false;
	s.x0 = x[0];
	s.x1 = x[1];
	s.y0 = y[0];
	s.y1 = y[1];
	s.dx = ft_abs(s.x1 - s.x0);
	s.dy = ft_abs(s.y1 - s.y0);
	// ray_test(game, &s);
	if (s.dy > s.dx)
	{
		ft_swap(&s.y0, &s.x0);
		ft_swap(&s.y1, &s.x1);
		ft_swap(&s.dx, &s.dy);
		dec = true;
	}
	s.m = 2 * s.dy - s.dx;
	bresenham(game, &s, dec, colour);
}

void	increment_angle(t_root *game, int x[2], int y[2], double r)
{
	double	xt;
	double	yt;

	xt = (x[1] - x[0]) * 90;
	yt = (y[1] - y[0]) * 90;
	// printf("xt: %f\nxy: %f\n", xt, yt);
	x[1] = ((xt * cos(r)) - (yt * sin(r)));
	y[1] = ((xt * sin(r)) + (yt * cos(r)));
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
	while (i < 1920)
	{
		game->me->rangle = rad;
		increment_angle(game, x, y, rad);
		rad += (FOV * (M_PI / 180)) / 1920;
		i += 1;
		x[1] = game->me->x[1];
		y[1] = game->me->y[1];
	}
}
