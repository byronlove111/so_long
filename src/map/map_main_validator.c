/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 04:45:44 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Effectue une validation complète de la carte de jeu.
 * Orchestre toutes les vérifications nécessaires incluant la structure,
 * les éléments et la connectivité du niveau de manière séquentielle.
 * @param level_data Structure contenant les données de la carte à valider
 * @return Code d'erreur MAP_OK si valide, code d'erreur spécifique sinon
 */
int	perform_complete_validation(t_map *level_data)
{
	int	validation_result;

	validation_result = validate_map_structure(level_data);
	if (validation_result != MAP_OK)
		return (display_validation_error(validation_result), validation_result);
	validation_result = verify_game_elements(level_data);
	if (validation_result != MAP_OK)
		return (display_validation_error(validation_result), validation_result);
	validation_result = analyze_level_connectivity(level_data);
	if (validation_result != MAP_OK)
		return (display_validation_error(validation_result), validation_result);
	return (MAP_OK);
} 
