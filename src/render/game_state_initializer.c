/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state_initializer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 05:05:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:07:02 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Configure l'état initial du jeu pour une nouvelle partie.
 * Initialise les compteurs, position du joueur et état des collectibles
 * en préparation du lancement de la session de jeu.
 * @param game_instance Structure principale du jeu à configurer
 * @return void
 */
void	configure_initial_game_state(t_game *game_instance)
{
	game_instance->player.moves = 0;
	game_instance->is_exit_reached = 0;
	locate_character_spawn(game_instance);
	calculate_item_total(game_instance);
} 
