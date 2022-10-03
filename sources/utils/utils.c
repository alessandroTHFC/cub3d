/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:26:11 by jbrown            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/23 09:24:40 by jbrown           ###   ########.fr       */
=======
/*   Updated: 2022/09/24 15:39:06 by jbrown           ###   ########.fr       */
>>>>>>> 53a6e78921c8db9aa256c784184aca140bc4b43c
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Converts a float array[2] to an int array[2] to be used in the pixel put
	function.	*/

int	*float_to_int(double fval[2], int ival[2])
{
	ival[0] = (int)fval[0];
	ival[1] = (int)fval[1];
	return (ival);
}

int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

int	direction(int curr, int dst)
{
	if (curr < dst)
		return (++curr);
	if (curr > dst)
		return (--curr);
	return (curr);
}
