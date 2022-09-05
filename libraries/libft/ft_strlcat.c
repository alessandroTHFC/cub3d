/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:49:42 by jbrown            #+#    #+#             */
/*   Updated: 2022/01/24 10:31:44 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while ((i + 1) < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}
