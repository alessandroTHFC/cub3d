/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/23 16:06:29 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "imported/libft.h"
# include "imported/mlx.h"
# include "imported/macros.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# define M_PI 3.14159265358979323846264338327950288
# define D_RAD 0.01745329251
# define TILE 20
# define FOV 60

typedef struct s_slope
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	dx;
	int	dy;
	int	m;
}	t_slope;

typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	double	x[2];
	double	y[2];
	int		xt[2];
	int		yt[2];
	double	rad;
	double	angle;
	double	ray_angle;
	double	col_x;
	double	col_y;
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
	t_img		*proj;
	t_player	*me;
	char		**map;
	int			map_height;
	int			map_width;
	int			player_count;
}	t_root;

/*	ERROR CHECKING	*/
char	**ft_splice(char *s, char c, t_root *game);
void	check_filetype(char *map_file);
int		internal_spaces(t_root *game);
void	error_checker(t_root *game);
int		horizontal_edges(t_root *game);
int		end_string_validity(t_root *game);
/*	INITIALISATION	*/
void	import_map(char *map_loc, t_root *game);
void	init_root(t_root *game);
void	init_player(t_root *game, int x, int y, char *dir);
/*	MOVEMENT	*/
void	rot_player(t_root *game, int dir);
void	move_player(t_root *game, int dir);
void	strafe_player(t_root *game, int dir);
bool	check_collision(t_root *game, double x, double y);
void	update_player(t_root *game);
/*	RAYCASTING	*/
void	set_ray_angle(t_root *game);
void	find_projection(t_root *game, int end[2]);
void	clear_projection(t_root *game);
/*	MEMORY FREE	*/
int		clean_exit(t_root *game);
void	free_map(char **map);
/*	MLX DRAWING	*/
void	draw_square(t_root *game, int colour, int x_offset, int y_offset);
void	draw_line(t_img *img, int *x, int *y, int colour);
void	draw_pixel(t_img *img, int *x_y, int colour);
void	draw_map(t_root *game, bool init);
void	clear_map(t_root *game);
/*	HOOKS	*/
int		key_press(int key, t_root *game);
/*	OTHER	*/
int		*float_to_int(double fval[2], int ival[2]);
int		cardinal_space(t_root *game, int row, int idx, char c);
int		direction(int curr, int dst);
void	ft_swap(int *a, int *b);
int		ft_abs(int i);

#endif