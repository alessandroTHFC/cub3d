#include "cub3d.h"

int horizontal_edges(t_root *game)
{
    int i;

    i = 0;
    while (game->map[0][i]) 
    {
        if (game->map[0][i] != '1' || game->map[0][i] != ' ')
            return (1)
        i++;
    }
    i = 0;
    while (game->map[game->map_height][i])
    {
        if (game->map[game->map_height][i] != '1' ||
                game->map[game->map_height][i] != ' ')
            return (1);
        i++;
    }
    return (0);
}
