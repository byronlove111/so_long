/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_connectivity_validator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:05:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/24 12:06:25 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Vérifie que tous les collectibles sont accessibles sans passer par la sortie.
 * Contrôle que chaque collectible peut être atteint sans traverser
 * la case de sortie qui doit rester inaccessible jusqu'à la fin.
 * @param connectivity_test Grille de test après analyse
 * @param level_data Structure de la carte originale
 * @return 1 si tous les collectibles sont accessibles, 0 sinon
 */
int	verify_collectibles_reachable(char **connectivity_test, t_map *level_data)
{
	int	row_index;
	int	col_index;

	row_index = 0;
	while (row_index < level_data->height)
	{
		col_index = 0;
		while (col_index < level_data->width)
		{
			if (level_data->map[row_index][col_index] == 'C' 
				&& connectivity_test[row_index][col_index] != 'V')
				return (0);
			col_index++;
		}
		row_index++;
	}
	return (1);
}

/**
 * Vérifie que la sortie est accessible une fois les collectibles récupérés.
 * Contrôle que la sortie peut être atteinte par le joueur après
 * avoir collecté tous les objets nécessaires du niveau.
 * @param connectivity_test Grille de test après analyse complète
 * @param level_data Structure de la carte originale
 * @return 1 si la sortie est accessible, 0 sinon
 */
int	verify_exit_reachable(char **connectivity_test, t_map *level_data)
{
	int	row_index;
	int	col_index;

	row_index = 0;
	while (row_index < level_data->height)
	{
		col_index = 0;
		while (col_index < level_data->width)
		{
			if (level_data->map[row_index][col_index] == 'E' 
				&& connectivity_test[row_index][col_index] != 'V')
				return (0);
			col_index++;
		}
		row_index++;
	}
	return (1);
}

/**
 * Effectue la validation d'accessibilité des collectibles.
 * Teste si tous les objets peuvent être collectés sans passer par la sortie.
 * @param level_data Structure contenant la carte à analyser
 * @param spawn_x Position X de départ du joueur
 * @param spawn_y Position Y de départ du joueur
 * @return MAP_OK si accessible, ERR_NO_PATH sinon
 */
static int	validate_collectibles_access(t_map *level_data, int spawn_x, 
		int spawn_y)
{
	char	**collectible_test;

	collectible_test = duplicate_level_grid(level_data);
	if (!collectible_test)
		return (ERR_MEMORY);
	mark_collectible_accessible_areas(collectible_test, spawn_x, spawn_y, 
		level_data->width, level_data->height);
	if (!verify_collectibles_reachable(collectible_test, level_data))
	{
		deallocate_string_array(collectible_test);
		return (ERR_NO_PATH);
	}
	deallocate_string_array(collectible_test);
	return (MAP_OK);
}

/**
 * Effectue la validation d'accessibilité de la sortie.
 * Teste si la sortie peut être atteinte après collecte des objets.
 * @param level_data Structure contenant la carte à analyser
 * @param spawn_x Position X de départ du joueur
 * @param spawn_y Position Y de départ du joueur
 * @return MAP_OK si accessible, ERR_NO_PATH sinon
 */
static int	validate_exit_access(t_map *level_data, int spawn_x, int spawn_y)
{
	char	**exit_test;

	exit_test = duplicate_level_grid(level_data);
	if (!exit_test)
		return (ERR_MEMORY);
	mark_all_accessible_areas(exit_test, spawn_x, spawn_y, 
		level_data->width, level_data->height);
	if (!verify_exit_reachable(exit_test, level_data))
	{
		deallocate_string_array(exit_test);
		return (ERR_NO_PATH);
	}
	deallocate_string_array(exit_test);
	return (MAP_OK);
}

/**
 * Analyse la connectivité complète du niveau de jeu.
 * Vérifie en deux étapes : d'abord l'accessibilité des collectibles
 * sans la sortie, puis l'accessibilité de la sortie avec tout le niveau.
 * @param level_data Structure contenant la carte à analyser
 * @return MAP_OK si connecté, code d'erreur sinon
 */
int	analyze_level_connectivity(t_map *level_data)
{
	int		spawn_x;
	int		spawn_y;
	int		result;

	locate_player_spawn(level_data, &spawn_x, &spawn_y);
	result = validate_collectibles_access(level_data, spawn_x, spawn_y);
	if (result != MAP_OK)
		return (result);
	result = validate_exit_access(level_data, spawn_x, spawn_y);
	if (result != MAP_OK)
		return (result);
	return (MAP_OK);
} 