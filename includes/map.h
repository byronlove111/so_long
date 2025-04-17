#ifndef MAP_H
# define MAP_H

# include "utils.h"
# include "so_long.h"

typedef struct s_map
{
	char	**matrix;
	int		width;
	int		height;
	int		total_collect;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_map;

typedef struct s_flood_context
{
	int	collectibles;
	int	exit_found;
	int	total_collect;
}	t_flood_context;

/* map_parser.c */
void	parse_map(const char *path, t_map *map);
int		has_ber_extension(const char *path);

/* map_init.c */
void	init_map(t_map *map);
int		init_map_reading(const char *path, t_map *map);

/* map_check.c */
void	check_rectangular(t_map *map);
void	check_walls_closed(t_map *map);
void	check_elements(t_map *map);

/* map_path.c */
void	check_path(t_map *map, int start_x, int start_y);

/* map_utils.c */
void	free_matrix(char **matrix);
int		count_char(t_map *map, char c);
int		find_char_pos(t_map *map, char c, int *x, int *y);
int		is_valid_char(char c);

/* map_valid.c */
void	validate_map(t_map *map);
int		flood_fill(char **map_copy, int x, int y, t_flood_context *ctx);

#endif
