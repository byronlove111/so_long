/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_accessibility_checker.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 04:47:37 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Vérifie que tous les objets collectables sont accessibles au joueur.
 * Compare la carte originale avec la carte marquée pour s'assurer
 * que chaque collectible peut être atteint par le joueur.
 * @param marked_grid Grille avec les zones accessibles marquées
 * @param original_level Carte originale contenant les collectibles
 * @return Code d'erreur MAP_OK si tous accessibles, ERR_NO_PATH sinon
 */
int	verify_collectibles_accessibility(char **marked_grid,
		t_map *original_level)
{
	int	row_checker;
	int	col_checker;

	row_checker = 0;
	while (row_checker < original_level->height)
	{
		col_checker = 0;
		while (col_checker < original_level->width)
		{
			if (original_level->map[row_checker][col_checker] == 'C'
				&& marked_grid[row_checker][col_checker] != 'F')
				return (ERR_NO_PATH);
			col_checker++;
		}
		row_checker++;
	}
	return (MAP_OK);
}

/**
 * Vérifie si une case adjacente à la sortie est accessible.
 * Contrôle les quatre directions autour de la sortie pour déterminer
 * si au moins une case adjacente est marquée comme accessible.
 * @param accessibility_map Carte marquée avec les zones accessibles
 * @param row_pos Position ligne de la sortie
 * @param col_pos Position colonne de la sortie
 * @param level_bounds Structure contenant les limites de la carte
 * @return 1 si au moins une case adjacente est accessible, 0 sinon
 */
static int	check_adjacent_accessibility(char **accessibility_map,
		int row_pos, int col_pos, t_map *level_bounds)
{
	if ((row_pos > 0
			&& accessibility_map[row_pos - 1][col_pos] == 'F')
		|| (row_pos < level_bounds->height - 1
			&& accessibility_map[row_pos + 1][col_pos] == 'F')
		|| (col_pos > 0
			&& accessibility_map[row_pos][col_pos - 1] == 'F')
		|| (col_pos < level_bounds->width - 1
			&& accessibility_map[row_pos][col_pos + 1] == 'F'))
		return (1);
	return (0);
}

/**
 * Recherche la position de la sortie dans la carte.
 * Parcourt toute la grille pour localiser le caractère 'E'
 * représentant la sortie du niveau.
 * @param original_level Carte originale contenant la sortie
 * @param exit_row Pointeur pour stocker la ligne de la sortie
 * @param exit_col Pointeur pour stocker la colonne de la sortie
 * @return 1 si la sortie est trouvée, 0 sinon
 */
static int	locate_exit_position(t_map *original_level, int *exit_row,
		int *exit_col)
{
	int	row_position;
	int	col_position;

	row_position = 0;
	while (row_position < original_level->height)
	{
		col_position = 0;
		while (col_position < original_level->width)
		{
			if (original_level->map[row_position][col_position] == 'E')
			{
				*exit_row = row_position;
				*exit_col = col_position;
				return (1);
			}
			col_position++;
		}
		row_position++;
	}
	return (0);
}

/**
 * Vérifie si la sortie du niveau est accessible au joueur.
 * Localise la sortie puis vérifie que les cases adjacentes
 * permettent au joueur de l'atteindre après avoir collecté tous les objets.
 * @param accessibility_map Carte marquée avec les zones accessibles
 * @param original_level Carte originale contenant la sortie
 * @return 1 si la sortie est accessible, 0 sinon
 */
int	verify_exit_accessibility(char **accessibility_map, t_map *original_level)
{
	int	exit_row;
	int	exit_col;

	if (!locate_exit_position(original_level, &exit_row, &exit_col))
		return (0);
	return (check_adjacent_accessibility(accessibility_map, exit_row,
			exit_col, original_level));
} 
