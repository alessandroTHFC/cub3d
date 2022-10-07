/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:07:30 by jbrown            #+#    #+#             */
/*   Updated: 2022/10/07 12:44:12 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	arr[3][3] = {
	{0xFF0000, 0xAA0000, 0x550000},
	{0xFF00, 0xAA00, 0x5500},
	{0xFF, 0xAA, 0x55}
};

double	ft_square(double d)
{
	return (d * d);
}

void	draw_cursor(t_root *game)
{
	int	x[2];
	int	y[2];

	x[0] = 1920 / 2 - 10;
	x[1] = x[0] + 19;
	y[0] = 1080 / 2;
	y[1] = y[0];
	draw_line(game->proj, x, y, 0xFF000000);
	x[0] += 10;
	x[1] -= 9;
	y[0] -= 10;
	y[1] += 9;
	draw_line(game->proj, x, y, 0xFF000000);
}

int	add_shade(int colour, int side, int height)
{
	int	red;
	int	green;
	int	blue;

	// colour += colour & 0xFFFFFF & (ft_abs(height) / 4);
	(void)height;
	if (side == 0)
		return (colour);
	red = (0xEF0000 & colour);
	green = (0xEF00 & colour);
	blue = (0xEF & colour);
	colour = red + green + blue;
	return (colour);
}

void	draw_wall(t_root *game, int x, int y, int side)
{
	int		y_end;
	int		x_y[2];
	int		i;
	int		y_err;
	int		x_err;
	int		scale;

	x_y[0] = x;
	x_y[1] = y;
	y_end = 1080 - y;
	scale = y_end - y;
	i = 0;
	y_err = 0;
	// printf("height: %i, width: %i\n", game->tex_h, game->tex_w);
	x_err = (game->me->text_i * 10) / TILE; // 2 should be replaced by x total of texture 
	while (x_y[1] != y_end)
	{
		if (x_y[1] > 0 && x_y[1] < 1080)
			draw_pixel(game->proj, x_y, add_shade(*(int *)(game->wall_texture + i + x_err), side, y));
		y_err++;
		if (y_err == scale / 10) //instead of 3, this would be the y total of the texture
		{
			y_err = 0;
			i++;
		}
		x_y[1]++;
	}
}

void	find_projection(t_root *game, int end[2])
{
	static int	scan;
	double		dist;
	int			height;
	int			side;

	side = find_side(game, end[0], end[1]);
	dist = sqrt(ft_square(game->me->x[0] - end[0])
			+ ft_square(game->me->y[0] - end[1]));
	if (game->fish_toggle)
		dist *= cos(game->me->rangle);
	height = 500 - ((TILE * 50) / (dist)) * 10;
	draw_wall(game, scan, height, side);//create_trgb(0, 255 - side, 255, dist / 4));
	scan += 1;
	if (scan == 1921)
	{
		draw_cursor(game);
		scan = 0;
	}
}
