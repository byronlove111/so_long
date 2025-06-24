/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:08:50 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/24 12:44:44 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Gère la collecte des objets dans le niveau de jeu.
 * Vérifie si la case de destination contient un collectible et le ramasse
 * en décrémentant le compteur et en remplaçant l'objet par du sol vide.
 * @param game_instance Structure principale du jeu
 * @param target_x Coordonnée X de la destination
 * @param target_y Coordonnée Y de la destination
 * @return void
 */
static void	handle_item_collection(t_game *game_instance, int target_x,
		int target_y)
{
	if (game_instance->map->map[target_y][target_x] == 'C')
	{
		game_instance->collectibles_count--;
		game_instance->map->map[target_y][target_x] = '0';
		ft_printf("Item collected! Remaining: %d\n",
			game_instance->collectibles_count);
	}
}

/**
 * Vérifie les conditions de sortie et termine le jeu si possible.
 * Contrôle que tous les collectibles ont été ramassés avant d'autoriser
 * la sortie du niveau et la fin de partie.
 * @param game_instance Structure principale du jeu
 * @param target_x Coordonnée X de la destination
 * @param target_y Coordonnée Y de la destination
 * @return 1 si sortie activée, 0 sinon
 */
static int	check_exit_conditions(t_game *game_instance, int target_x,
		int target_y)
{
	if (game_instance->map->map[target_y][target_x] == 'E')
	{
		if (game_instance->collectibles_count == 0)
		{
			ft_printf("Congratulations! Level completed in %d moves!\n",
				game_instance->player.moves + 1);
			terminate_game_application(game_instance);
		}
		else
			ft_printf("Collect all items before exiting!\n");
		return (1);
	}
	return (0);
}

/**
 * Met à jour la position du personnage sur la carte de jeu.
 * Efface l'ancienne position, place le joueur à la nouvelle position
 * et incrémente le compteur de mouvements avec affichage.
 * @param game_instance Structure principale du jeu
 * @param new_x Nouvelle coordonnée X du joueur
 * @param new_y Nouvelle coordonnée Y du joueur
 * @return void
 */
static void	update_character_position(t_game *game_instance, int new_x,
		int new_y)
{
	game_instance->map->map[game_instance->player.y]
	[game_instance->player.x] = '0';
	game_instance->player.x = new_x;
	game_instance->player.y = new_y;
	game_instance->map->map[new_y][new_x] = 'P';
	game_instance->player.moves++;
	ft_printf("Moves count: %d\n", game_instance->player.moves);
	display_complete_level(game_instance->graphics, game_instance->map);
}

/**
 * Exécute le déplacement du personnage selon la direction donnée.
 * Calcule la nouvelle position, vérifie les collisions, gère les interactions
 * avec les objets et met à jour l'état du jeu.
 * @param game_instance Structure principale du jeu
 * @param offset_x Déplacement horizontal (-1, 0, 1)
 * @param offset_y Déplacement vertical (-1, 0, 1)
 * @return void
 */
void	execute_player_movement(t_game *game_instance, int offset_x,
		int offset_y)
{
	int	destination_x;
	int	destination_y;

	destination_x = game_instance->player.x + offset_x;
	destination_y = game_instance->player.y + offset_y;
	if (game_instance->map->map[destination_y][destination_x] == '1')
		return ;
	handle_item_collection(game_instance, destination_x, destination_y);
	if (check_exit_conditions(game_instance, destination_x, destination_y))
		return ;
	update_character_position(game_instance, destination_x, destination_y);
}

/**
 * Gestionnaire principal des entrées clavier du joueur.
 * Analyse les touches pressées et déclenche les actions correspondantes
 * incluant les déplacements directionnels et la sortie du jeu.
 * @param key_code Code de la touche pressée
 * @param game_instance Structure principale du jeu
 * @return 0 pour continuer le jeu
 */
int	process_keyboard_input(int key_code, t_game *game_instance)
{
	if (key_code == KEY_ESC)
		terminate_game_application(game_instance);
	if (key_code == KEY_W || key_code == KEY_UP)
		execute_player_movement(game_instance, 0, -1);
	if (key_code == KEY_S || key_code == KEY_DOWN)
		execute_player_movement(game_instance, 0, 1);
	if (key_code == KEY_A || key_code == KEY_LEFT)
		execute_player_movement(game_instance, -1, 0);
	if (key_code == KEY_D || key_code == KEY_RIGHT)
		execute_player_movement(game_instance, 1, 0);
	return (0);
}
