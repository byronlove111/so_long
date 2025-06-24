/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_connectivity_analyzer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:25:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:15:34 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Crée une copie complète de la grille de niveau pour les tests.
 * Duplique chaque ligne de la carte originale pour permettre
 * les modifications sans affecter la carte principale du jeu.
 * @param level_data Structure contenant la carte originale
 * @return Pointeur vers la grille dupliquée ou NULL si échec
 */
char	**duplicate_level_grid(t_map *level_data)
{
	char	**grid_copy;
	int		row_index;

	grid_copy = malloc(sizeof(char *) * (level_data->height + 1));
	if (!grid_copy)
		return (NULL);
	row_index = 0;
	while (row_index < level_data->height)
	{
		grid_copy[row_index] = ft_strdup(level_data->map[row_index]);
		if (!grid_copy[row_index])
		{
			while (row_index > 0)
			{
				row_index--;
				free(grid_copy[row_index]);
			}
			free(grid_copy);
			return (NULL);
		}
		row_index++;
	}
	grid_copy[row_index] = NULL;
	return (grid_copy);
}

/**
 * Marque récursivement toutes les zones accessibles depuis une position.
 * Utilise un algorithme de remplissage par diffusion pour identifier
 * tous les espaces atteignables depuis le point de départ donné.
 * @param test_grid Grille de test modifiable
 * @param pos_x Position X actuelle
 * @param pos_y Position Y actuelle
 * @param grid_width Largeur de la grille
 * @param grid_height Hauteur de la grille
 * @return void
 */
void	mark_accessible_areas(char **test_grid, int pos_x, int pos_y, 
		int grid_width, int grid_height)
{
	if (pos_x < 0 || pos_x >= grid_width || pos_y < 0 || pos_y >= grid_height)
		return ;
	if (test_grid[pos_y][pos_x] == '1' || test_grid[pos_y][pos_x] == 'V')
		return ;
	test_grid[pos_y][pos_x] = 'V';
	mark_accessible_areas(test_grid, pos_x + 1, pos_y, grid_width, grid_height);
	mark_accessible_areas(test_grid, pos_x - 1, pos_y, grid_width, grid_height);
	mark_accessible_areas(test_grid, pos_x, pos_y + 1, grid_width, grid_height);
	mark_accessible_areas(test_grid, pos_x, pos_y - 1, grid_width, grid_height);
}

/**
 * Localise la position de spawn du joueur dans la grille.
 * Parcourt la carte pour trouver le caractère 'P' représentant
 * la position initiale du personnage jouable.
 * @param level_data Structure contenant la carte de jeu
 * @param spawn_x Pointeur pour stocker la coordonnée X
 * @param spawn_y Pointeur pour stocker la coordonnée Y
 * @return void
 */
void	locate_player_spawn(t_map *level_data, int *spawn_x, int *spawn_y)
{
	int	row_pos;
	int	col_pos;

	row_pos = 0;
	while (row_pos < level_data->height)
	{
		col_pos = 0;
		while (col_pos < level_data->width)
		{
			if (level_data->map[row_pos][col_pos] == 'P')
			{
				*spawn_x = col_pos;
				*spawn_y = row_pos;
				return ;
			}
			col_pos++;
		}
		row_pos++;
	}
}

/**
 * Vérifie les conditions d'accessibilité requises pour le niveau.
 * Contrôle que tous les collectibles et la sortie sont marqués
 * comme accessibles après l'analyse de connectivité.
 * @param connectivity_test Grille de test après analyse
 * @param level_data Structure de la carte originale
 * @return 1 si accessible, 0 sinon
 */
static int	verify_accessibility_requirements(char **connectivity_test, 
		t_map *level_data)
{
	int	row_index;
	int	col_index;

	row_index = 0;
	while (row_index < level_data->height)
	{
		col_index = 0;
		while (col_index < level_data->width)
		{
			if ((level_data->map[row_index][col_index] == 'C' 
				|| level_data->map[row_index][col_index] == 'E') 
				&& connectivity_test[row_index][col_index] != 'V')
				return (0);
			col_index++;
		}
		row_index++;
	}
	return (1);
}

/**
 * Analyse la connectivité complète du niveau de jeu.
 * Vérifie que tous les éléments importants sont accessibles depuis
 * la position de départ du joueur en utilisant un test de remplissage.
 * @param level_data Structure contenant la carte à analyser
 * @return MAP_OK si connecté, code d'erreur sinon
 */
int	analyze_level_connectivity(t_map *level_data)
{
	char	**connectivity_test;
	int		spawn_x;
	int		spawn_y;
	int		is_accessible;

	connectivity_test = duplicate_level_grid(level_data);
	if (!connectivity_test)
		return (ERR_MEMORY);
	locate_player_spawn(level_data, &spawn_x, &spawn_y);
	mark_accessible_areas(connectivity_test, spawn_x, spawn_y, 
		level_data->width, level_data->height);
	is_accessible = verify_accessibility_requirements(connectivity_test, 
			level_data);
	deallocate_string_array(connectivity_test);
	if (!is_accessible)
		return (ERR_NO_PATH);
	return (MAP_OK);
} 
