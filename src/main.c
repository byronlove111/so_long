/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:34 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:25:38 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Gestionnaire de fermeture de fenêtre
 * Fonction wrapper qui appelle terminate_game_application et
 * retourne int pour mlx_hook
 * @param game_instance Structure principale du jeu
 * @return 0 (jamais atteint car terminate_game_application termine le programme)
 */
static int	close_window_handler(t_game *game_instance)
{
	terminate_game_application(game_instance);
	return (0);
}

/**
 * Fonction principale du programme so_long
 * Valide les arguments, initialise le jeu et lance la boucle d'événements
 * @param argc Nombre d'arguments de la ligne de commande
 * @param argv Tableau des arguments de la ligne de commande
 * @return Code de sortie du programme (0 si succès)
 */
int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Usage: %s [map_file.ber]\n", argv[0]);
		return (1);
	}
	game = create_game_instance(argv[1]);
	if (!game)
		return (1);
	display_complete_level(game->graphics, game->map);
	ft_printf("Moves: 0\n");
	mlx_key_hook(game->graphics->window, process_keyboard_input, game);
	mlx_hook(game->graphics->window, 17, 0, close_window_handler, game);
	mlx_loop(game->graphics->mlx);
	return (0);
}
