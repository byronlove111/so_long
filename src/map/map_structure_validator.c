/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_structure_validator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 04:45:54 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Vérifie si la carte forme un rectangle valide avec des dimensions minimales.
 * Contrôle que toutes les lignes ont la même largeur et que les dimensions
 * respectent les exigences minimales du jeu (au moins 3x3).
 * @param level_data Structure contenant les données de la carte
 * @return Code d'erreur MAP_OK si valide, code d'erreur spécifique sinon
 */
int	verify_rectangular_shape(t_map *level_data)
{
	int	row_counter;
	int	current_width;

	if (level_data->height < 3 || level_data->width < 3)
		return (ERR_MAP_TOO_SMALL);
	row_counter = 0;
	while (row_counter < level_data->height)
	{
		current_width = calculate_row_width(level_data->map[row_counter]);
		if (current_width != level_data->width)
			return (ERR_NOT_RECTANGLE);
		row_counter++;
	}
	return (MAP_OK);
}

/**
 * Vérifie que la carte est entièrement entourée de murs (caractère '1').
 * Contrôle les bordures de la carte pour s'assurer qu'elles sont
 * composées uniquement de murs pour empêcher le joueur de sortir.
 * @param level_data Structure contenant les données de la carte
 * @return Code d'erreur MAP_OK si valide, ERR_NO_WALLS sinon
 */
int	verify_boundary_walls(t_map *level_data)
{
	int	row_position;
	int	col_position;

	if (!level_data || !level_data->map)
		return (0);
	row_position = 0;
	while (row_position < level_data->height)
	{
		col_position = 0;
		while (col_position < level_data->width)
		{
			if ((row_position == 0 || row_position == level_data->height - 1)
				|| (col_position == 0 || col_position == level_data->width - 1))
			{
				if (level_data->map[row_position][col_position] != '1')
					return (ERR_NO_WALLS);
			}
			col_position++;
		}
		row_position++;
	}
	return (MAP_OK);
}

/**
 * Effectue une validation complète de la structure de la carte.
 * Vérifie la forme rectangulaire et l'intégrité des murs de bordure
 * pour s'assurer que la carte respecte les contraintes structurelles.
 * @param level_data Structure contenant les données de la carte à valider
 * @return Code d'erreur MAP_OK si valide, code d'erreur spécifique sinon
 */
int	validate_map_structure(t_map *level_data)
{
	int	validation_result;

	validation_result = verify_rectangular_shape(level_data);
	if (validation_result != MAP_OK)
		return (validation_result);
	validation_result = verify_boundary_walls(level_data);
	if (validation_result != MAP_OK)
		return (validation_result);
	return (MAP_OK);
} 
