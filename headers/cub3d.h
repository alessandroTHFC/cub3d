/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/05 11:50:19 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "imported/libft.h"
# include "imported/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# define UP 126
# define DOWN 0
# define LEFT 1
# define RIGHT 2
# define EXIT 53
# define BUFFER_SIZE 1000

typedef struct s_minmap
{
	int	win_width;
	int	win_height;
	int	x_offset;
	int	y_offset;
}	t_minmap;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_root
{
	t_mlx		*mlx;
	t_minmap	*minmap;
	char		**map;
	int			player_count;
}	t_root;

void	check_filetype(char *map_file, t_root *game);
void	import_map(char *map_loc, t_root *game);
void	clean_exit(t_root *game);
void	draw_square(t_root *game, int colour, int x_offset, int y_offset);
void	draw_line(t_mlx *mlx, int *x, int *y, int colour);
void	draw_pixel(t_mlx *mlx, int x, int y, int colour);

#endif