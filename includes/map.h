#ifndef MAP_H
# define MAP_H

# include "utils.h"
# include "so_long.h"

typedef struct s_map
{
    char  **matrix;
    int     width;
    int     height;
    int     total_collect;
}  t_map;

void    parse_map(const char *path, t_map *map);
int		has_ber_extension(const char *path);
void    validate_map(t_map *map);
void    check_rectangular(t_map *map);
void    check_walls_closed(t_map *map);
void    check_elements(t_map *map);
void    check_path(t_map *map, int start_x, int start_y);
void    free_matrix(char **matrix);

#endif
