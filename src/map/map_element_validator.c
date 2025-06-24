/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_element_validator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:15:34 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Vérifie si un caractère fait partie des éléments valides du jeu.
 * Contrôle que le caractère correspond à un élément autorisé :
 * sol (0), mur (1), joueur (P), sortie (E), ou collectible (C).
 * @param game_char Caractère à valider
 * @return 1 si le caractère est valide, 0 sinon
 */
int	is_valid_char(char game_char)
{
	return (game_char == '0' || game_char == '1' || game_char == 'P'
		|| game_char == 'E' || game_char == 'C');
}

/**
 * Compte le nombre de chaque type d'élément dans la carte de jeu.
 * Parcourt toute la grille et maintient des compteurs séparés
 * pour les joueurs, sorties et objets collectables.
 * @param level_data Structure contenant les données de la carte
 * @param player_total Pointeur vers le compteur de joueurs
 * @param exit_total Pointeur vers le compteur de sorties
 * @param collectible_total Pointeur vers le compteur de collectibles
 * @return void
 */
void	tally_game_elements(t_map *level_data, int *player_total,
		int *exit_total, int *collectible_total)
{
	int	row_scanner;
	int	col_scanner;

	row_scanner = 0;
	*player_total = 0;
	*exit_total = 0;
	*collectible_total = 0;
	while (row_scanner < level_data->height)
	{
		col_scanner = 0;
		while (col_scanner < level_data->width)
		{
			if (level_data->map[row_scanner][col_scanner] == 'P')
				(*player_total)++;
			else if (level_data->map[row_scanner][col_scanner] == 'E')
				(*exit_total)++;
			else if (level_data->map[row_scanner][col_scanner] == 'C')
				(*collectible_total)++;
			col_scanner++;
		}
		row_scanner++;
	}
}

/**
 * Valide que les quantités d'éléments respectent les règles du jeu.
 * Vérifie qu'il y a exactement un joueur, une sortie et au moins
 * un objet collectable dans la carte.
 * @param player_count Nombre de joueurs trouvés
 * @param exit_count Nombre de sorties trouvées
 * @param collectible_count Nombre de collectibles trouvés
 * @return Code d'erreur MAP_OK si valide, code d'erreur spécifique sinon
 */
int	verify_element_quantities(int player_count, int exit_count,
		int collectible_count)
{
	if (player_count == 0)
		return (ERR_NO_PLAYER);
	if (player_count > 1)
		return (ERR_MULTI_PLAYER);
	if (exit_count == 0)
		return (ERR_NO_EXIT);
	if (exit_count > 1)
		return (ERR_MULTI_EXIT);
	if (collectible_count == 0)
		return (ERR_NO_COLLECT);
	return (MAP_OK);
}

/**
 * Vérifie la validité et le nombre des éléments de jeu dans la carte.
 * Contrôle que tous les caractères sont valides et que les quantités
 * d'éléments (joueur, sortie, collectibles) respectent les règles.
 * @param level_data Structure contenant les données de la carte
 * @return Code d'erreur MAP_OK si valide, code d'erreur spécifique sinon
 */
int	verify_game_elements(t_map *level_data)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
	int	row_scanner;
	int	col_scanner;

	row_scanner = 0;
	while (row_scanner < level_data->height)
	{
		col_scanner = 0;
		while (col_scanner < level_data->width)
		{
			if (!is_valid_char(level_data->map[row_scanner][col_scanner]))
				return (ERR_INVALID_CHAR);
			col_scanner++;
		}
		row_scanner++;
	}
	tally_game_elements(level_data, &player_count, &exit_count,
		&collectible_count);
	return (verify_element_quantities(player_count, exit_count,
			collectible_count));
}
