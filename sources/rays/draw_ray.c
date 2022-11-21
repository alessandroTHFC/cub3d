/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:28:37 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/24 15:34:49 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_direction(int i, int j)
{
	if (i < j)
		return (1);
	return (-1);
}

void	ray_vector(int vect[2], int x, int y, int dec)
{
	if (dec)
	{
		vect[0] = y;
		vect[1] = x;
	}
	else
	{
		vect[1] = y;
		vect[0] = x;
	}
}
