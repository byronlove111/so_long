/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 05:10:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:09:06 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Libère un tableau de chaînes de caractères alloué dynamiquement.
 * Parcourt chaque élément du tableau pour libérer individuellement
 * chaque chaîne avant de libérer le tableau lui-même.
 * @param string_array Tableau de chaînes à libérer
 * @return void
 */
void	deallocate_string_array(char **string_array)
{
	int	array_index;

	array_index = 0;
	if (!string_array)
		return ;
	while (string_array[array_index])
	{
		free(string_array[array_index]);
		array_index++;
	}
	free(string_array);
}

/**
 * Termine proprement l'application de jeu avec nettoyage complet.
 * Libère toutes les ressources allouées incluant la carte, les graphiques
 * et la structure principale avant de quitter le programme.
 * @param game_instance Structure principale du jeu à nettoyer
 * @return void (fonction ne retourne jamais)
 */
void	terminate_game_application(t_game *game_instance)
{
	if (game_instance->map)
	{
		if (game_instance->map->map)
			deallocate_string_array(game_instance->map->map);
		free(game_instance->map);
	}
	if (game_instance->graphics)
		cleanup_graphics_resources(game_instance->graphics);
	free(game_instance);
	exit(0);
}
