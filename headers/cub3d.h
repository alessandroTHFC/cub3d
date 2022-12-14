/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/17 11:04:28 by jbrown           ###   ########.fr       */
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

# define M_PI		3.14159265358979323846264338327950288
# define TILE		100000
# define FOV		1000

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

typedef struct s_dda
{
	int		x_y[2];
	float	h_check[2];
	float	v_check[2];
	float	v_step[2];
	float	h_step[2];
	double	dx;
	double	dy;
	double	a_tan;
	double	n_tan;
}	t_dda;

typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	double	x[2];
	double	y[2];
	int		xt[2];
	int		yt[2];
	int		text_i;
	double	rad;
	double	angle;
	double	rangle;
}	t_player;

typedef struct s_minmap
{
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

typedef struct s_textures
{
	t_img	img;
	int		h;
	int		w;
}	t_textures;

typedef struct s_root
{
	t_mlx		*mlx;
	t_minmap	*minmap;
	t_img		*proj;
	t_player	*me;
	t_textures	**texts;
	int			colours[2];
	char		**paths;
	int			i;
	int			tex_w;
	int			tex_h;
	char		**map;
	int			map_height;
	int			map_width;
	int			win_height;
	int			win_width;
	int			fov;
	int			tile;
	int			player_count;
	bool		key_pressed[512];
	bool		map_toggle;
	bool		fish_toggle;
}	t_root;

/*	MAP_READING */
char	*get_textures(t_root *game, char *file);
void	clear_layer(t_root *game, t_img *img);
void	draw_layer(t_root *game, t_img *img);
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
void	apply_textures(t_root *game);
int		add_texture(t_root *game, int dir, char *file, int i);
int		add_colour(t_root *game, int type, char *file, int i);
/*	MOVEMENT	*/
void	rot_player(t_root *game, int dir);
void	move_player(t_root *game, int dir);
void	strafe_player(t_root *game, int dir);
bool	check_collision(t_root *game, double x, double y);
void	update_player(t_root *game);
/*	RAYCASTING	*/
void	set_ray_angle(t_root *game);
void	find_projection(t_root *game, int end[2]);
int		ray_direction(int i, int j);
void	ray_vector(int vect[2], int x, int y, int dec);
int		find_side(t_root *game, int x, int y);
bool	is_wall(char **map, int x, int y);
void	normalise_ray(t_root *game, int x_y[2], int colour);
float	dist(float ax, float ay, int bx, int by);
/*	MEMORY FREE	*/
int		clean_exit(t_root *game);
void	free_map(char **map);
/*	MLX DRAWING	*/
void	draw_square(t_root *game, int colour, int x_offset, int y_offset);
void	draw_background(t_root *game);
void	clear_layer(t_root *game, t_img *img);
void	draw_line(t_img *img, int *x, int *y, int colour);
void	draw_pixel(t_img *img, int *x_y, int colour);
void	draw_map(t_root *game, bool init);
void	tile_size(t_root *game);
void	draw_cursor(t_root *game);
/*	HOOKS	*/
int		key_press(int key, t_root *game);
int		key_release(int key, t_root *game);
int		mouse_move(int move, t_root *game);
int		game_hook(t_root *game);
/*	OTHER	*/
int		*float_to_int(double fval[2], int ival[2]);
int		cardinal_space(t_root *game, int row, int idx, char c);
int		direction(int curr, int dst);
void	ft_swap(int *a, int *b);
int		ft_abs(int i);
int		create_trgb(int t, int r, int g, int b);

#endif