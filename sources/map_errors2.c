#include "cub3d.h"

///Horizontal Edges function error checks the top and bottom row of the map.
///it specifically checks for unwanted characters on the outer edges.
///For the map to be valid, the horizontal borders should only consist of 1's or spaces.
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

///End String Validity function error checks the right side of the map boundary.
///It uses strlen to find the final character in each map row string.
///The end of every string MUST be a 1. Any other character would be invalid and imply
///that the map is not enclosed. 
int end_string_validity(t_root *game)
{
    int y;
    size_t len;

    y = 0;
    while (game->map[y])
    {
        len = ft_strlen(game->map[y]);
        if (game->map[y][len] != '1')
        {
            printf("\e[31m\e[1mError\nRight Map Border has invalid Character \e[0m \n");
            return(1)
        }
        y++;
    }
    return(0);
}

///Internal Spaces function error checks the maps interior. This function looks only at whether
///the character being checked is either 0, N, S, E, W, for the map to be valid none of these characters
///should have an empty space next to them. It checks by looking at a specific character on the map and 
///checks the characters on all four side (y - 1, y + 1, x - 1, x + 1)
int internal_spaces(t_root *game)
{
    int row;
    int idx;
    char    c;

    row = 1;
    idx = 1;
    while (game->map[row])
    {
        while(game->map[row][idx])
        {
            c = game->map[row][idx];
            if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
            {
                if (game->map[row -1][idx] == ' ' || game->map[row +1][idx] == ' ' ||
                        game->map[row][idx -1] == ' ' || game->map[row][idx +1] == ' ')
                {
                    printf("\e[31m\e[1mError\n  Invalid Spaces in the Map. Fucked \e[0m \n");
                    return(1)
                }
                idx++;
            }
            row++;
        }
    }
    return (0);
}