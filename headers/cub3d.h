/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:45 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/02 13:48:15 by jbrown           ###   ########.fr       */
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

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	**map;
}	t_mlx;

void	import_map(char *map_loc, t_mlx *mlx);

#endif