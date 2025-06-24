/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:48:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/24 12:41:45 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Gère les échecs d'initialisation avec nettoyage approprié.
 * Libère toutes les ressources allouées selon le stade d'échec
 * et affiche un message d'erreur informatif pour le débogage.
 * @param instance Structure de jeu partiellement initialisée
 * @param cleanup_stage Niveau de nettoyage requis (0-3)
 * @return void
 */
void	handle_init_failure(t_game *instance, int cleanup_stage)
{
	ft_printf("Initialization failed at stage %d\n", cleanup_stage);
	if (cleanup_stage >= 1 && instance->map)
	{
		if (instance->map->map)
			deallocate_string_array(instance->map->map);
		free(instance->map);
	}
	if (cleanup_stage >= 2 && instance->graphics)
		cleanup_graphics_resources(instance->graphics);
	if (instance)
		free(instance);
}

/**
 * Configure le système graphique avec initialisation complète.
 * Alloue la structure graphique, l'initialise et configure
 * tous les composants nécessaires au rendu du jeu.
 * @param instance Structure principale du jeu
 * @return 1 si succès, 0 si échec
 */
int	configure_graphics_system(t_game *instance)
{
	instance->graphics = malloc(sizeof(t_graphics));
	if (!instance->graphics)
		return (0);
	reset_graphics_structure(instance->graphics);
	if (!initialize_graphics_system(instance->graphics, instance->map))
	{
		free(instance->graphics);
		return (0);
	}
	return (1);
}

/**
 * Initialise l'état de jeu avec configuration des données.
 * Configure les paramètres initiaux du joueur, compteurs
 * et autres variables d'état nécessaires au gameplay.
 * @param instance Structure principale du jeu
 * @return void
 */
void	initialize_game_state(t_game *instance)
{
	configure_initial_game_state(instance);
}

/**
 * Crée et initialise une instance complète de jeu.
 * Orchestre l'initialisation de tous les composants incluant
 * carte, graphiques et état de jeu avec gestion d'erreur robuste.
 * @param level_file Chemin vers le fichier de carte
 * @return Pointeur vers l'instance de jeu ou NULL si échec
 */
t_game	*create_game_instance(char *level_file)
{
	t_game	*instance;

	instance = malloc(sizeof(t_game));
	if (!instance)
		return (NULL);
	instance->map = malloc(sizeof(t_map));
	if (!instance->map || !setup_level_data(instance, level_file))
	{
		handle_init_failure(instance, 1);
		return (NULL);
	}
	if (!configure_graphics_system(instance))
	{
		handle_init_failure(instance, 2);
		return (NULL);
	}
	initialize_game_state(instance);
	return (instance);
}
