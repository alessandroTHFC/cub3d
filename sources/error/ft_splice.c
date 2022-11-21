/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:15:24 by jbrown            #+#    #+#             */
/*   Updated: 2022/11/07 12:52:29 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	findstring(int *first, int last, char c, char *s)
{
	while (s[*first] == c)
		(*first)++;
	last = *first;
	while (s[last] && s[last] != c)
		last++;
	return (last);
}

static int	numofstrings(char *s, char c, t_root *game)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || !(s[i + 1])) && s[i] != c)
		{
			r++;
		}
		i++;
	}
	game->map_height = r - 1;
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

static char	**freestrings(char **s, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_splice(char *s, char c, t_root *game)
{
	int		first;
	int		last;
	int		i;
	char	**strs;
	int		no_of_strs;

	no_of_strs = numofstrings(s, c, game);
	strs = malloc(sizeof(*strs) * (no_of_strs + 1));
	if (!strs)
		return (strs);
	first = 0;
	i = 0;
	while (s[first] && i < no_of_strs)
	{
		last = findstring(&first, last, c, s);
		strs[i] = fillstring(s, first, last);
		if (!strs[i])
			return (freestrings(strs, i));
		first = last;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
