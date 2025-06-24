/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 04:45:48 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Dessine une tuile spécifique à l'écran selon son type de caractère.
 * Place d'abord le sol de base puis ajoute l'élément spécifique
 * (mur, collectible, sortie, joueur) par-dessus selon le type.
 * @param display_system Système graphique contenant les textures et la fenêtre
 * @param grid_row Position verticale dans la grille
 * @param grid_col Position horizontale dans la grille
 * @param element_type Caractère représentant le type d'élément à dessiner
 * @return void
 */
static void	draw_single_tile(t_graphics *display_system, int grid_row,
		int grid_col, char element_type)
{
	int		pixel_x;
	int		pixel_y;
	void	*sprite_texture;

	pixel_x = grid_col * SPRITE_SIZE;
	pixel_y = grid_row * SPRITE_SIZE;
	mlx_put_image_to_window(display_system->mlx, display_system->window,
		display_system->textures.floor, pixel_x, pixel_y);
	if (element_type == '1')
		sprite_texture = display_system->textures.wall;
	else if (element_type == 'C')
		sprite_texture = display_system->textures.collect;
	else if (element_type == 'E')
		sprite_texture = display_system->textures.exit;
	else if (element_type == 'P')
		sprite_texture = display_system->textures.player;
	else
		return ;
	mlx_put_image_to_window(display_system->mlx, display_system->window,
		sprite_texture, pixel_x, pixel_y);
}

/**
 * Effectue le rendu complet de la carte de jeu à l'écran.
 * Parcourt toute la grille de jeu et dessine chaque tuile
 * avec sa texture appropriée selon son type d'élément.
 * @param display_system Système graphique pour l'affichage
 * @param level_data Structure contenant les données de la carte
 * @return 1 en cas de succès, 0 en cas d'erreur
 */
int	display_complete_level(t_graphics *display_system, t_map *level_data)
{
	int	current_row;
	int	current_col;

	if (!display_system || !level_data || !level_data->map)
		return (0);
	current_row = 0;
	while (current_row < level_data->height)
	{
		current_col = 0;
		while (current_col < level_data->width)
		{
			draw_single_tile(display_system, current_row, current_col,
				level_data->map[current_row][current_col]);
			current_col++;
		}
		current_row++;
	}
	return (1);
}
