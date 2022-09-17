/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:26:11 by jbrown            #+#    #+#             */
/*   Updated: 2022/09/17 14:26:42 by jbrown           ###   ########.fr       */
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
