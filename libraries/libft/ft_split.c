/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:54:23 by jbrown            #+#    #+#             */
/*   Updated: 2022/01/28 15:53:25 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	findstring(int *first, int last, char c, char *s)
{
	while (s[*first] == c)
		(*first)++;
	last = *first;
	while (s[last] && s[last] != c)
		last++;
	return (last);
}

static int	numofstrings(char *s, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || !(s[i + 1])) && s[i] != c)
			r++;
		i++;
	}
	return (r);
}

static char	*fillstring(char *s1, int first, int last)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(*s2) * ((last - first) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while ((first + i) < last && s1[first + i])
	{
		s2[i] = s1[first + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	freestrings(char **s, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	int		first;
	int		last;
	int		i;
	char	**strs;

	strs = malloc(sizeof(*strs) * (numofstrings((char *) s, c) + 1));
	if (!strs)
		return (strs);
	first = 0;
	i = 0;
	while (s[first] && i < numofstrings((char *) s, c))
	{
		last = findstring(&first, last, c, (char *) s);
		strs[i] = fillstring((char *) s, first, last);
		if (!strs[i])
		{
			freestrings(strs, i);
			return (NULL);
		}
		first = last;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
