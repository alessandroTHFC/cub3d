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
			r++;
		i++;
	}
    game->map_height = r;
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

char	**ft_splice(char const *s, char c, t_root *game)
{
	int		first;
	int		last;
	int		i;
	char	**strs;

	strs = malloc(sizeof(*strs) * (numofstrings((char *) s, c, game) + 1));
	if (!strs)
		return (strs);
	first = 0;
	i = 0;
	while (s[first] && i < numofstrings((char *) s, c, game))
	{
		last = findstring(&first, last, c, (char *) s);
        game->map_width = last - first;
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