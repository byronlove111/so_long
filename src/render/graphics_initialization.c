/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_initialization.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 05:02:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:07:08 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialise la connexion avec le serveur graphique MLX.
 * Établit la connexion de base nécessaire pour toutes les opérations
 * graphiques ultérieures du système de rendu.
 * @param render_system Structure contenant les données graphiques
 * @return 1 si succès, 0 si échec
 */
int	establish_mlx_connection(t_graphics *render_system)
{
	if (!render_system)
		return (0);
	render_system->mlx = mlx_init();
	if (!render_system->mlx)
		return (0);
	return (1);
}

/**
 * Crée la fenêtre principale de l'application de jeu.
 * Calcule automatiquement les dimensions selon la taille de la carte
 * et initialise la fenêtre avec le titre approprié.
 * @param render_system Structure graphique principale
 * @param level_data Données de la carte pour calculer les dimensions
 * @return 1 si succès, 0 si échec
 */
int	create_main_window(t_graphics *render_system, t_map *level_data)
{
	int	window_width;
	int	window_height;

	if (!render_system || !level_data || !render_system->mlx)
		return (0);
	window_width = level_data->width * SPRITE_SIZE;
	window_height = level_data->height * SPRITE_SIZE;
	render_system->window = mlx_new_window(render_system->mlx, window_width,
			window_height, "so_long");
	if (!render_system->window)
		return (0);
	render_system->height = window_height;
	render_system->width = window_width;
	return (1);
}

/**
 * Initialise complètement le système de rendu graphique.
 * Orchestre l'initialisation MLX, la création de fenêtre et le chargement
 * des ressources avec gestion d'erreur intégrée.
 * @param render_system Structure graphique à initialiser
 * @param level_data Données de la carte de jeu
 * @return 1 si succès, 0 si échec
 */
int	initialize_graphics_system(t_graphics *render_system, t_map *level_data)
{
	if (!render_system || !level_data)
		return (-1);
	if (!establish_mlx_connection(render_system))
	{
		cleanup_graphics_resources(render_system);
		return (0);
	}
	if (!create_main_window(render_system, level_data))
	{
		cleanup_graphics_resources(render_system);
		return (0);
	}
	if (!load_game_assets(render_system))
	{
		cleanup_graphics_resources(render_system);
		return (0);
	}
	return (1);
} 
