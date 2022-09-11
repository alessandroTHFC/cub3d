/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/09 11:07:56 by jbrown           ###   ########.fr       */
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
# include <math.h>
# include <stdbool.h>

# define W 126
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define EXIT 53
# define BUFFER_SIZE 1000

typedef struct s_slope
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	dx;
	int	dy;
	int	m;
	int	x;
	int	y;
	int	err;
}	t_slope;

typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	int		x[2];
	int		y[2];
	double	rad;
}	t_player;

typedef struct s_minmap
{
	int	win_width;
	int	win_height;
	int	x_offset;
	int	y_offset;
	int	max_x;
	int	max_y;
}	t_minmap;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	*addr;
	t_img	*minmap;
	int		pixel_bits;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_root
{
	t_mlx		*mlx;
	t_minmap	*minmap;
	t_player	*me;
	char		**map;
	int			map_height;
	int			map_width;
	int			player_count;
}	t_root;

char	**ft_splice(char const *s, char c, t_root *game);
void	check_filetype(char *map_file, t_root *game);
int		internal_spaces(t_root *game);
void	error_checker(t_root *game);
int		horizontal_edges(t_root *game);
int		end_string_validity(t_root *game);
void	import_map(char *map_loc, t_root *game);
void	clean_exit(t_root *game);
void	draw_square(t_root *game, int colour, int x_offset, int y_offset);
void	draw_line(t_img *img, int *x, int *y, int colour);
void	draw_pixel(t_img *img, int *x_y, int colour);
void	init_player(t_root *game, int x, int y, char dir);
void	rot_player(t_root *game);

#endif