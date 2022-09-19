/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:20:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/19 09:36:52 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	printf("5\n");
	x /= (TILE + 1);
	y /= (TILE + 1);
	printf("x: %i, y: %i\n", x, y);
	printf("%s\n", map[y - 1]);
	if (map[y][x] && map[y][x] == '1')
		return (true);
	printf("6\n");
	return (false);
}

static void	bresenham(t_root *game, t_slope *s, bool dec, int colour)
{
	int	x_y[2];

	s->m = 2 * s->dy - s->dx;
	while (!(is_wall(game->map, s->x0, s->y0)))
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
		draw_pixel(game->mlx->minmap, x_y, colour);
		if (s->m < 0)
			s->m = s->m + 2 * s->dy;
		else
		{
			s->y0 = direction(s->y0, s->y1);
			s->m = s->m + 2 * s->dy - 2 * s->dx;
		}
	}
}

void	draw_ray(t_root *game, int *x, int *y, int colour)
{
	t_slope	s;

	printf("3\n");
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
	printf("4\n");
}

void	set_ray_angle(t_root *game)
{
	int	x[2];
	int	y[2];

	printf("%s\n", game->map[0]);
	x[0] = game->me->x[0];
	x[1] = game->me->x[1];
	y[0] = game->me->y[0];
	y[1] = game->me->y[1];
	printf("2\n");
	draw_ray(game, x, y, 0x01013492);
}
