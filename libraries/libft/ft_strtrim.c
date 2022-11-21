/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:06:05 by jbrown            #+#    #+#             */
/*   Updated: 2022/01/28 14:25:31 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trimmatch(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	int		i;
	char	*s2;

	if (!(s1 && set))
		return (NULL);
	first = 0;
	while (trimmatch(s1[first], set) && s1[first])
		first++;
	last = ft_strlen(s1);
	while (trimmatch(s1[last - 1], set) && last > first)
		last--;
	s2 = malloc((last - first + 1) * sizeof(*s2));
	if (!s2)
		return (NULL);
	i = 0;
	while (first < last)
		s2[i++] = s1[first++];
	s2[i] = '\0';
	return (&s2[0]);
}
