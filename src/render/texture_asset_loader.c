/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_asset_loader.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 05:03:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:07:15 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Charge une texture individuelle depuis un fichier XPM.
 * Convertit le fichier XPM en image MLX utilisable pour le rendu
 * avec validation des dimensions et gestion d'erreur.
 * @param mlx_instance Pointeur vers l'instance MLX
 * @param texture_ptr Pointeur vers la texture à charger
 * @param asset_path Chemin vers le fichier XPM
 * @return 1 si succès, 0 si échec
 */
static int	load_individual_asset(void *mlx_instance, void **texture_ptr, 
		char *asset_path)
{
	int	sprite_width;
	int	sprite_height;

	*texture_ptr = mlx_xpm_file_to_image(mlx_instance, asset_path, 
			&sprite_width, &sprite_height);
	if (!*texture_ptr)
	{
		ft_putstr_fd("Error: Failed to load texture asset\n", 2);
		return (0);
	}
	return (1);
}

/**
 * Charge toutes les ressources graphiques du jeu.
 * Initialise l'ensemble des textures nécessaires au rendu incluant
 * personnage, murs, objets collectables, sol et sortie.
 * @param render_system Structure graphique contenant les textures
 * @return 1 si succès, 0 si échec
 */
int	load_game_assets(t_graphics *render_system)
{
	if (!render_system || !render_system->mlx)
		return (0);
	if (!load_individual_asset(render_system->mlx, 
			&render_system->textures.player, PLAYER_XPM))
		return (0);
	if (!load_individual_asset(render_system->mlx, 
			&render_system->textures.wall, WALL_XPM))
		return (0);
	if (!load_individual_asset(render_system->mlx, 
			&render_system->textures.exit, EXIT_XPM))
		return (0);
	if (!load_individual_asset(render_system->mlx, 
			&render_system->textures.floor, FLOOR_XPM))
		return (0);
	if (!load_individual_asset(render_system->mlx, 
			&render_system->textures.collect, COLLECT_XPM))
		return (0);
	return (1);
} 
