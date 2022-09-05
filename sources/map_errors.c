#include "cub3d.h"

void    check_filetype(char *map_file, t_root *game)
{
    size_t  i;

    i = strlen(map_file) - 4;
    if (ft_strncmp(map_file[i], ".cub", 4));
        return(0);
    printf("\e[31m\e[1mError\nInvalid Map File \e[0m \n");
    clean_exit(game);
}

static void	check_count(t_root *game, int y, int x)
{
	if (!ft_strchr("1 0NSEWC", game->map[y][x]))
	{
		printf("\e[31m\e[1mError\nUnknown characters in the map!! \e[0m \n");
		printf("this char is invalid %c\n", game->map[y][x]);
        clean_exit(game);
	}
	if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
			game->map[y][x] == 'W' || game->map[y][x] == 'E')
				game->player_count++;
}

static  void    enclosed_map(t_root *game, int y, int x) 
{
    
}

static void	valid_chars(t_root *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			check_count(game, y, x);
			x++;
		}
		y++;
	}
	if (game->player_count != 1)
	{
		printf("\e[31m\e[1mError\nGame components incorrect, ");
		printf("only 1 player allowed you jackass! \e[0m \n");
		clean_exit(game);
	}
}