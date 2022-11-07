/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:47:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 15:17:34 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_textures(t_root *game)
{
	int				i;
	t_textures		*tmp;
	t_textures		**tex;

	tex = malloc(sizeof(*tex) * 4);
	i = 0;
	while (i < 4)
	{
		tmp = malloc(sizeof(*tmp));
		tmp->img.img = mlx_xpm_file_to_image(game->mlx->mlx,
				game->paths[i], &tmp->w, &tmp->h);
		if (!tmp->img.img)
		{
			printf("NOPE!\n");
			exit(1);
		}
		tex[i] = tmp;
		tex[i]->addr = mlx_get_data_addr(tex[i]->img.img,
				&tex[i]->img.pixel_bits, &tex[i]->img.line_len,
				&tex[i]->img.endian);
		i++;
	}
	game->texts = tex;
}

/*	Sets the initial player orientation to the correct direction.	*/

void	init_orientation(char dir, double x[2], double y[2])
{
	*x = TILE / 2;
	*y = TILE / 2;
	if (dir == 'N')
		*y = 0;
	if (dir == 'E')
		*x = TILE;
	if (dir == 'S')
		*y = TILE;
	if (dir == 'W')
		*x = 0;
}

/*	Sets initial values for player, including position on map and player
	angle.	*/

void	init_player(t_root *game, int x, int y, char *dir)
{
	static t_player	me;

	x /= game->tile;
	x *= TILE;
	y /= game->tile;
	y *= TILE;
	me.tile_x = x;
	me.tile_y = y;
	me.x[0] = TILE / 2 + me.tile_x;
	me.y[0] = TILE / 2 + me.tile_y;
	me.rad = 5 * M_PI / 180;
	init_orientation(*dir, &me.x[1], &me.y[1]);
	*dir = '0';
	me.x[1] += me.tile_x;
	me.y[1] += me.tile_y;
	me.angle = atan2(me.y[1] - me.y[0], me.x[1] - me.x[0]);
	game->me = &me;
}
