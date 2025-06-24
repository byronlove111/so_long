/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_connectivity_analyzer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:25:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/24 12:10:22 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Libère la mémoire d'une grille partiellement allouée en cas d'erreur.
 * Nettoie toutes les lignes déjà allouées avant l'échec d'allocation.
 * @param grid_copy Grille partiellement allouée
 * @param row_index Index de la ligne où l'allocation a échoué
 * @return void
 */
static void	cleanup_partial_grid(char **grid_copy, int row_index)
{
	while (row_index > 0)
	{
		row_index--;
		free(grid_copy[row_index]);
	}
	free(grid_copy);
}

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
			cleanup_partial_grid(grid_copy, row_index);
			return (NULL);
		}
		row_index++;
	}
	grid_copy[row_index] = NULL;
	return (grid_copy);
}

/**
 * Marque récursivement les zones accessibles pour collecter les objets.
 * Utilise un algorithme de remplissage qui traite la sortie comme obstacle
 * temporaire pour vérifier l'accessibilité des collectibles uniquement.
 * @param test_grid Grille de test modifiable
 * @param pos_x Position X actuelle
 * @param pos_y Position Y actuelle
 * @param grid_width Largeur de la grille
 * @param grid_height Hauteur de la grille
 * @return void
 */
void	mark_collectible_accessible_areas(char **test_grid, int pos_x, int pos_y, 
		int grid_width, int grid_height)
{
	if (pos_x < 0 || pos_x >= grid_width || pos_y < 0 || pos_y >= grid_height)
		return ;
	if (test_grid[pos_y][pos_x] == '1' || test_grid[pos_y][pos_x] == 'V' 
		|| test_grid[pos_y][pos_x] == 'E')
		return ;
	test_grid[pos_y][pos_x] = 'V';
	mark_collectible_accessible_areas(test_grid, pos_x + 1, pos_y, 
		grid_width, grid_height);
	mark_collectible_accessible_areas(test_grid, pos_x - 1, pos_y, 
		grid_width, grid_height);
	mark_collectible_accessible_areas(test_grid, pos_x, pos_y + 1, 
		grid_width, grid_height);
	mark_collectible_accessible_areas(test_grid, pos_x, pos_y - 1, 
		grid_width, grid_height);
}

/**
 * Marque récursivement toutes les zones accessibles incluant la sortie.
 * Utilise un algorithme de remplissage standard pour vérifier
 * l'accessibilité générale de tous les éléments du niveau.
 * @param test_grid Grille de test modifiable
 * @param pos_x Position X actuelle
 * @param pos_y Position Y actuelle
 * @param grid_width Largeur de la grille
 * @param grid_height Hauteur de la grille
 * @return void
 */
void	mark_all_accessible_areas(char **test_grid, int pos_x, int pos_y, 
		int grid_width, int grid_height)
{
	if (pos_x < 0 || pos_x >= grid_width || pos_y < 0 || pos_y >= grid_height)
		return ;
	if (test_grid[pos_y][pos_x] == '1' || test_grid[pos_y][pos_x] == 'V')
		return ;
	test_grid[pos_y][pos_x] = 'V';
	mark_all_accessible_areas(test_grid, pos_x + 1, pos_y, 
		grid_width, grid_height);
	mark_all_accessible_areas(test_grid, pos_x - 1, pos_y, 
		grid_width, grid_height);
	mark_all_accessible_areas(test_grid, pos_x, pos_y + 1, 
		grid_width, grid_height);
	mark_all_accessible_areas(test_grid, pos_x, pos_y - 1, 
		grid_width, grid_height);
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
