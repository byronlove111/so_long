/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:34 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:21:24 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "so_long.h"

/*
** ============================================================================
** STRUCTURE PRINCIPALE DU JEU
** ============================================================================
*/

/**
 * Structure principale du jeu contenant tous les composants
 * Regroupe le joueur, la carte, les graphiques et l'état du jeu
 */
typedef struct s_game
{
	t_player		player;
	t_map			*map;
	t_graphics		*graphics;
	int				collectibles_count;
	int				is_exit_reached;
}					t_game;

/*
** ============================================================================
** FONCTIONS DE GESTION DU JEU - MODULE ENGINE
** ============================================================================
*/

/**
 * Localise la position de spawn du personnage dans la carte
 * Scanne la grille pour trouver le caractère 'P' et configure
 * les coordonnées initiales du joueur dans la structure de jeu.
 * @param game_instance Structure principale du jeu
 * @return void
 */
void				locate_character_spawn(t_game *game_instance);

/**
 * Calcule le nombre total d'objets collectables dans le niveau
 * Parcourt la carte pour compter tous les collectibles 'C'
 * et initialise le compteur dans la structure de jeu.
 * @param game_instance Structure principale du jeu
 * @return void
 */
void				calculate_item_total(t_game *game_instance);

/**
 * Configure les données de niveau depuis un fichier carte
 * Charge et valide le fichier .ber spécifié, initialise
 * la structure de carte et vérifie la conformité du niveau.
 * @param game_instance Structure principale du jeu
 * @param level_file Chemin vers le fichier de carte .ber
 * @return 1 si succès, 0 si échec
 */
int					setup_level_data(t_game *game_instance, char *level_file);

/**
 * Crée et initialise une instance complète de jeu
 * Orchestre l'initialisation de tous les composants incluant
 * carte, graphiques et état de jeu avec gestion d'erreur robuste.
 * @param level_file Chemin vers le fichier de carte
 * @return Pointeur vers l'instance de jeu ou NULL si échec
 */
t_game				*create_game_instance(char *level_file);

#endif
