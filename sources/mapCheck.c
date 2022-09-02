#include "cub3d.h"

static void check_count(t_root *game, int y, int x)
{
    if(!ft_strchr("1  0NSEWC", game->map[y][x]))
    {
        printf("\e[31m\e[1mError\nUnknown characters in the map!! \e[0m \n");
		printf("this char is invalid %c\n", game->map[y][x]);
    }
    if(game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
            game->map[y][x] == "W" || game->map[y][x] == 'E')
                game->player_count++;
}

void    valid_chars(t_root *game)
{
    int x;
    int y;

    y = 0;
    while(game->map[y])
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
        printf("\e[31m\e[1mError\nGame components incorrect,only 1 player allowed you jackass! \e[0m \n");
        free_exit(game);
    }
}