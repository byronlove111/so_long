/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 05:04:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:07:11 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialise une structure graphique avec des valeurs par défaut.
 * Remet à zéro tous les pointeurs et valeurs numériques pour éviter
 * les erreurs de segmentation lors des opérations ultérieures.
 * @param render_system Structure graphique à initialiser
 * @return void
 */
void	reset_graphics_structure(t_graphics *render_system)
{
	render_system->mlx = NULL;
	render_system->window = NULL;
	render_system->textures.player = NULL;
	render_system->textures.exit = NULL;
	render_system->textures.collect = NULL;
	render_system->textures.floor = NULL;
	render_system->textures.wall = NULL;
	render_system->width = 0;
	render_system->height = 0;
}

/**
 * Libère toutes les ressources graphiques allouées.
 * Détruit les textures, fenêtre et connexion MLX avec gestion
 * conditionnelle pour éviter les double-libérations.
 * @param render_system Structure graphique à nettoyer
 * @return void
 */
void	cleanup_graphics_resources(t_graphics *render_system)
{
	if (!render_system)
		return ;
	if (render_system->mlx)
	{
		if (render_system->textures.player)
			mlx_destroy_image(render_system->mlx, 
				render_system->textures.player);
		if (render_system->textures.exit)
			mlx_destroy_image(render_system->mlx, render_system->textures.exit);
		if (render_system->textures.collect)
			mlx_destroy_image(render_system->mlx, 
				render_system->textures.collect);
		if (render_system->textures.floor)
			mlx_destroy_image(render_system->mlx, 
				render_system->textures.floor);
		if (render_system->textures.wall)
			mlx_destroy_image(render_system->mlx, render_system->textures.wall);
		if (render_system->window)
			mlx_destroy_window(render_system->mlx, render_system->window);
#ifndef __APPLE__
		mlx_destroy_display(render_system->mlx);
#endif
		free(render_system->mlx);
		render_system->mlx = NULL;
	}
	free(render_system);
} 
