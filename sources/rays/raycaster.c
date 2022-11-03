/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/03 13:11:01 by jbrown           ###   ########.fr       */
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

	// if (x[1] < 0 || x[1] >= 1920)
	// 	return ;
	x[0] = game->me->x[0] * TILE_DRAW / TILE;
	x[1] = x_y[0] * TILE_DRAW / TILE;
	y[0] = game->me->y[0] * TILE_DRAW / TILE;
	y[1] = x_y[1] * TILE_DRAW / TILE;
	// printf("normalised\nx: %i\ny: %i\n\n", x[1], y[1]);
	if (game->map_toggle)
		draw_line(game->proj, x, y, colour);
	// (void)colour;
}

float	dist(float ax, float ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	more_ray(t_root *game)
{
	t_dda	dda;
	float	angle;
	float	distx;
	float	disty;

	angle = game->me->rangle + game->me->angle;
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	// printf("angle: %i\n", (int)(angle * (180 / M_PI)));
	dda.a_tan = -1 / tan(angle);
	dda.n_tan = -tan(angle);
	dda.x_y[0] = game->me->x[0];
	dda.x_y[1] = game->me->y[0];
	if (angle > M_PI)
	{
		dda.h_check[1] = (dda.x_y[1] / TILE) * TILE - 1;
		dda.h_check[0] = (dda.x_y[1] - dda.h_check[1]) * dda.a_tan + dda.x_y[0];
		dda.h_step[1] = -TILE;
	}
	if (angle < M_PI)
	{
		dda.h_check[1] = (dda.x_y[1] / TILE) * TILE + TILE;
		dda.h_check[0] = (dda.x_y[1] - dda.h_check[1]) * dda.a_tan + dda.x_y[0];
		dda.h_step[1] = TILE;
	}
	dda.h_step[0] = -dda.h_step[1] * dda.a_tan;
	if (angle > (M_PI / 2) && angle < (3 * M_PI / 2))
	{
		dda.v_check[0] = (dda.x_y[0] / TILE) * TILE - 1;
		dda.v_check[1] = (dda.x_y[0] - dda.v_check[0]) * dda.n_tan + dda.x_y[1];
		dda.v_step[0] = -TILE;
	}
	if (angle < (M_PI / 2) || angle > (3 * M_PI / 2))
	{
		dda.v_check[0] = (dda.x_y[0] / TILE) * TILE + TILE;
		dda.v_check[1] = (dda.x_y[0] - dda.v_check[0]) * dda.n_tan + dda.x_y[1];
		dda.v_step[0] = TILE;
	}
	dda.v_step[1] = -dda.v_step[0] * dda.n_tan;
	if (angle == M_PI || !angle)
	{
		dda.v_check[0] = dda.x_y[0];
		dda.v_check[1] = dda.x_y[1];
		dda.h_check[0] = dda.x_y[0];
		dda.h_check[1] = dda.x_y[1];
		dda.h_step[1] = TILE;
		dda.h_step[0] = 0;
		dda.v_step[0] = TILE;
		dda.v_step[1] = 0;
	}
	dda.dx = dist(dda.x_y[0], dda.x_y[1], dda.v_check[0], dda.v_check[1]);
	distx = dist(dda.x_y[0], dda.x_y[1], game->me->x[0] + dda.v_step[0], game->me->y[0] + dda.v_step[1]);
	dda.dy = dist(dda.x_y[0], dda.x_y[1], dda.h_check[0], dda.h_check[1]);
	disty = dist(dda.x_y[0], dda.x_y[1], game->me->x[0] + dda.h_step[0], game->me->y[0] + dda.h_step[1]);
	if (dda.dx > dda.dy)
	{
		dda.x_y[0] = dda.h_check[0];
		dda.x_y[1] = dda.h_check[1];
	}
	else
	{
		dda.x_y[0] = dda.v_check[0];
		dda.x_y[1] = dda.v_check[1];
	}
	dda.dx = distx;
	dda.dy = disty;
	int	i	= 0;

	while (game->map[dda.x_y[1] / TILE][dda.x_y[0] / TILE] != '1')
	{
		dda.dx = dist(dda.x_y[0], dda.x_y[1], dda.v_check[0], dda.v_check[1]);
		dda.dy = dist(dda.x_y[0], dda.x_y[1], dda.h_check[0], dda.h_check[1]);
		if (dda.dy < dda.dx)
		{
			dda.x_y[0] = dda.h_check[0];
			dda.x_y[1] = dda.h_check[1];
			if (game->map[dda.h_check[1] / TILE][dda.h_check[0] / TILE] == '1')
			{
				// normailse_ray(game, dda.x_y, 0xFF00);
				// normailse_ray(game, dda.v_check, 0xFF00FF);
				break ;
			}
			dda.h_check[0] += dda.h_step[0];
			dda.h_check[1] += dda.h_step[1];
			// dda.dy += disty;
		}
		else
		{
			dda.x_y[0] = dda.v_check[0];
			dda.x_y[1] = dda.v_check[1];
			if (game->map[dda.v_check[1] / TILE][dda.v_check[0] / TILE] == '1')
			{
				// normailse_ray(game, dda.x_y, 0xFF00FF);
				// normailse_ray(game, dda.v_check, 0xFF00);
				break ;
			}
			dda.v_check[0] += dda.v_step[0];
			dda.v_check[1] += dda.v_step[1];
			// dda.dx += distx;
		}
		i++;
		if (i > 50)
			break ;
	}
	normailse_ray(game, dda.x_y, 0xFF00FF);
	find_projection(game, dda.x_y);
}

void	ray_test(t_root *game, t_slope *s)
{
	// int		y_int;
	// int		x_other;
	double	curr_angle;
	int		y_step;
	int		x_step;
	int		x_y[2];
	int		tmpxy[2];
	float	distH, distV;
	int		i = 0;

	curr_angle = (game->me->rangle);
	if (curr_angle > (2 * M_PI))
		curr_angle -= (2 * M_PI);
	if (curr_angle < 0)
		curr_angle += (2 * M_PI);
	float	aTan = -1 / tan(curr_angle);
	// printf("init x: %i\ninit y: %i\n", s->x0, s->y0);
	if (curr_angle > M_PI)
	{
		tmpxy[1] = (s->y0 / TILE) * TILE - 1;
		tmpxy[0] = (s->y0 - tmpxy[1]) * aTan + s->x0;
		y_step = -TILE;
		x_step = -y_step * aTan;
	}
	else// if (curr_angle < M_PI)
	{
		tmpxy[1] = (s->y0 / TILE) * TILE + TILE;
		tmpxy[0] = (s->y0 - tmpxy[1]) * aTan + s->x0;
		y_step = TILE;
		x_step = -y_step * aTan;
	}
	if (curr_angle == M_PI || !curr_angle)
	{
		tmpxy[0] = s->x0;
		tmpxy[1] = s->y0;
		y_step = TILE;
		x_step = 0;
	}
	x_y[0] = tmpxy[0];
	x_y[1] = tmpxy[1];
	// printf("working init x: %d\nworking init y: %d\n", x_y[0], x_y[1]);
	while (i < 20)
	{
		if (x_y[0] <= 0 || x_y[0] >= 2900 || x_y[1] <= 0 || x_y[1] >= 1400)
		{
			break ;
		}
		if (is_wall(game->map, x_y[0], x_y[1]))
		{
			break ;
		}
		else
		{
			x_y[0] += x_step;
			x_y[1] += y_step;
			i++;
		}
		// printf("x: %d\ny: %d\n", x_y[0], x_y[1]);
	}
	distH = dist(s->x0, s->y0, x_y[0], x_y[1]);

	tmpxy[0] = x_y[0];
	tmpxy[1] = x_y[1];

	float nTan = -tan(curr_angle);
	if (curr_angle > (M_PI / 2) && curr_angle < (3 * M_PI / 2))
	{
		x_y[0] = (s->x0 / TILE) * TILE - 1;
		x_y[1] = (s->x0 - x_y[0]) * nTan + s->y0;
		x_step = -TILE;
		y_step = -x_step * nTan;
	}
	else// if (curr_angle < (M_PI / 2) || curr_angle > (3 * M_PI / 2))
	{
		x_y[0] = (s->x0 / TILE) * TILE + TILE;
		x_y[1] = (s->x0 - x_y[0]) * nTan + s->y0;
		x_step = TILE;
		y_step = -x_step * nTan;
	}
	if (curr_angle == M_PI || !curr_angle)
	{
		x_y[0] = s->x0;
		x_y[1] = s->y0;
		x_step = TILE;
		y_step = 0;
	}
	// printf("working init x: %d\nworking init y: %d\n", x_y[0], x_y[1]);
	while (i < 20)
	{
		// printf("rayx: %i\nrayy: %i\n", x_y[0], x_y[1]);
		// printf("x: %d\ny: %d\n", x_y[0], x_y[1]);
		if (x_y[0] <= 0 || x_y[0] >= 2900 || x_y[1] <= 0 || x_y[1] >= 1400)
		{
			break ;
		}
		if (game->map[x_y[1] / TILE][x_y[0] / TILE] == '1')
		{
			break ;
		}
		else
		{
			x_y[0] += x_step;
			x_y[1] += y_step;
			i++;
		}
	}
	distV = dist(s->x0, s->y0, x_y[0], x_y[1]);

	if (distV > distH)
	{
		x_y[0] = tmpxy[0];
		x_y[1] = tmpxy[1];
	}
	// printf("x0: %i, x1: %i\ny0: %i, y1: %i\n", game->me->x[0], x_y[0], s->y0, x_y[1]);
	// normailse_ray(game, x_y, 0xFF00FF);
	find_projection(game, x_y);
}

// static void	bresenham(t_root *game, t_slope *s, bool dec, int colour)
// {
// 	int	x_y[2];
// 	int	x_dir;
// 	int	y_dir;
// 	int	x;

// 	x_dir = ray_direction(s->x0, s->x1);
// 	y_dir = ray_direction(s->y0, s->y1);
// 	x = s->x0;
// 	while (ft_abs(s->x0 - x) < (TILE) * 50)
// 	{
// 		s->x0 += x_dir;
// 		ray_vector(x_y, s->x0, s->y0, dec);
// 		if (is_wall(game->map, x_y[0], x_y[1]))
// 			break ;
// 		if (s->m < 0)
// 			s->m = s->m + 2 * s->dy;
// 		else
// 		{
// 			s->y0 += y_dir;
// 			s->m = s->m + 2 * s->dy - 2 * s->dx;
// 		}
// 	}
// 	// if (game->map_toggle)
// 	// 	normailse_ray(game, x_y, colour);
// 	find_projection(game, x_y);
// 	(void)colour;
// }

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
	// game->me->rangle = atan((double)s.dy / s.dx);
	// ray_test(game, &s);
	more_ray(game);
	(void)colour;
	// if (s.dy > s.dx)
	// {
	// 	ft_swap(&s.y0, &s.x0);
	// 	ft_swap(&s.y1, &s.x1);
	// 	ft_swap(&s.dx, &s.dy);
	// 	dec = true;
	// }
	// s.m = 2 * s.dy - s.dx;
	// bresenham(game, &s, dec, colour);
}

void	increment_angle(t_root *game, int x[2], int y[2], double r)
{
	double	xt;
	double	yt;

	xt = (x[1] - x[0]) * 100;
	yt = (y[1] - y[0]) * 100;
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
		i++;
		x[1] = game->me->x[1];
		y[1] = game->me->y[1];
	}
}
