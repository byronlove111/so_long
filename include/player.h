/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:34 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:21:24 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

/* Inclusion des codes de touches selon l'OS */
# ifdef __APPLE__
#  include "keys_macos.h"
# else
#  include "keys_linux.h"
# endif

# include "so_long.h"

/*
** ============================================================================
** STRUCTURE DU JOUEUR
** ============================================================================
*/

/**
 * Structure représentant le joueur dans le jeu
 * Contient la position actuelle et le compteur de mouvements
 * pour le suivi des performances et la logique de déplacement
 */
typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}	t_player;

/*
** ============================================================================
** DÉCLARATION FORWARD POUR ÉVITER LES DÉPENDANCES CIRCULAIRES
** ============================================================================
*/
typedef struct s_game	t_game;

/*
** ============================================================================
** FONCTIONS DE CONTRÔLE DU JOUEUR
** ============================================================================
*/

/**
 * Gestionnaire principal des entrées clavier du joueur
 * Analyse les touches pressées et déclenche les actions correspondantes
 * incluant les déplacements directionnels et la sortie du jeu.
 * @param key_code Code de la touche pressée
 * @param game_instance Structure principale du jeu
 * @return 0 pour continuer le jeu
 */
int		process_keyboard_input(int key_code, t_game *game_instance);

/**
 * Exécute le déplacement du personnage selon la direction donnée
 * Calcule la nouvelle position, vérifie les collisions, gère les interactions
 * avec les objets et met à jour l'état du jeu.
 * @param game_instance Structure principale du jeu
 * @param offset_x Déplacement horizontal (-1, 0, 1)
 * @param offset_y Déplacement vertical (-1, 0, 1)
 * @return void
 */
void	execute_player_movement(t_game *game_instance,
			int offset_x, int offset_y);

#endif
