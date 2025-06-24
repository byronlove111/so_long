/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:34 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/24 12:34:11 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_graphics	t_graphics;

/* Map Error Codes */
# define MAP_OK 0
# define ERR_NO_PLAYER 1
# define ERR_MULTI_PLAYER 2
# define ERR_NO_EXIT 3
# define ERR_MULTI_EXIT 4
# define ERR_NO_COLLECT 5
# define ERR_INVALID_CHAR 6
# define ERR_NOT_RECTANGLE 7
# define ERR_NO_WALLS 8
# define ERR_MAP_TOO_SMALL 9
# define ERR_NO_PATH 10
# define ERR_MEMORY 11

typedef struct s_map
{
	int						width;
	int						height;
	char					**map;
	int						player_x;
	int						player_y;
}							t_map;

typedef struct s_pos
{
	int x;
	int y;
}							t_pos;

/* Map File Handler */
int							load_game_level(t_map *level_data, char *level_filename);
size_t						calculate_row_width(char *text_line);

/* Map Structure Validator */
int							verify_rectangular_shape(t_map *level_data);
int							verify_boundary_walls(t_map *level_data);
int							validate_map_structure(t_map *level_data);

/* Map Element Validator */
int							is_valid_char(char game_char);
void						tally_game_elements(t_map *level_data, int *player_total, int *exit_total, int *collectible_total);
int							verify_element_quantities(int player_count, int exit_count, int collectible_count);
int							verify_game_elements(t_map *level_data);

/* Map Connectivity Analyzer */
char						**duplicate_level_grid(t_map *level_data);
void						mark_collectible_accessible_areas(char **test_grid, t_pos pos, t_map *bounds);
void						mark_all_accessible_areas(char **test_grid, t_pos pos, t_map *bounds);
void						locate_player_spawn(t_map *level_data, int *spawn_x, int *spawn_y);
int							analyze_level_connectivity(t_map *level_data);

/* Map Connectivity Validator */
int							verify_collectibles_reachable(char **connectivity_test, t_map *level_data);
int							verify_exit_reachable(char **connectivity_test, t_map *level_data);



/* Map Error Manager */
void						display_validation_error(int error_type);

/* Map Render Engine */
int							display_complete_level(t_graphics *display_system, t_map *level_data);

/* Map Main Validator */
int							perform_complete_validation(t_map *level_data);

/* Utility Functions */
void						print_char_tab(char **tab);

#endif
