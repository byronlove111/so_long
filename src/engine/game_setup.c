/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/24 14:49:56 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Parcourt la carte de jeu pour localiser les coordonnées de spawn du joueur.
 * Itère à travers chaque cellule de la grille pour trouver le caractère 'P'
 * et met à jour la position du joueur dans l'instance de jeu.

 * @param instance Pointeur vers la structure principale
 * du jeu contenant les données de carte
 * @return void
 */
void	locate_character_spawn(t_game *instance)
{
	int	row;
	int	col;

	ft_printf("Locating character spawn point...\n");
	row = 0;
	while (row < instance->map->height)
	{
		col = 0;
		while (col < instance->map->width)
		{
			ft_printf("Scanning grid [%d,%d]: '%c'\n", row, col,
				instance->map->map[row][col]);
			if (instance->map->map[row][col] == 'P')
			{
				instance->player.x = col;
				instance->player.y = row;
				ft_printf("Character spawn located at coordinates [%d,%d]\n", row,
					col);
				return ;
			}
			col++;
		}
		row++;
	}
	ft_printf("ERROR: No player spawn point detected in level data!\n");
}

/**
 *
 * Analyse l'ensemble de la carte de jeu pour compter les objets 
 * collectables (caractères 'C').
 * Met à jour le nombre total et le nombre restant d'objets collectables
 * dans l'instance de jeu pour suivre la progression du jeu.
 *
 * @param instance Pointeur vers la structure principale du jeu 
 * contenant les données de carte
 * @return void
 */
void	calculate_item_total(t_game *instance)
{
	int	y_pos;
	int	x_pos;

	ft_printf("Analyzing item distribution across level...\n");
	instance->collectibles_count = 0;
	y_pos = 0;
	while (y_pos < instance->map->height)
	{
		x_pos = 0;
		while (x_pos < instance->map->width)
		{
			if (instance->map->map[y_pos][x_pos] == 'C')
				instance->collectibles_count++;
			x_pos++;
		}
		y_pos++;
	}
	ft_printf("Total collectible items detected: %d\n",
		instance->collectibles_count);
}

/**

 * Initialise le composant carte du jeu en chargeant les données de 
 * niveau depuis un fichier.
 * Alloue la mémoire pour la structure de carte,
 * charge le contenu de la carte et valide
 * le format de carte et la conformité aux règles.
 * @param instance Pointeur vers la structure principale du jeu
 * @param level_file Chemin vers le fichier de carte .ber à charger
 * @return 1 en cas d'initialisation réussie, 0 en cas d'échec
 */
int	setup_level_data(t_game *instance, char *level_file)
{
	instance->map = malloc(sizeof(t_map) * 1);
	if (!instance->map)
		return (0);
	if (!load_game_level(instance->map, level_file))
		return (0);
	if (perform_complete_validation(instance->map) != MAP_OK)
		return (0);
	return (1);
}
