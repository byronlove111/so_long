/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:34 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:21:24 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

/*
** ============================================================================
** CONSTANTES GRAPHIQUES
** ============================================================================
*/
# define SPRITE_SIZE 40
# define WALL_XPM "./asset/wall.xpm"
# define FLOOR_XPM "./asset/floor.xpm"
# define COLLECT_XPM "./asset/collect.xpm"
# define EXIT_XPM "./asset/exit.xpm"
# define PLAYER_XPM "./asset/player.xpm"

/*
** ============================================================================
** STRUCTURES GRAPHIQUES
** ============================================================================
*/

/**
 * Structure contenant toutes les textures du jeu
 * Stocke les pointeurs vers les images MLX pour chaque élément visuel
 */
typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*collect;
	void		*exit;
	void		*player;
	int			size;
}				t_textures;

/**
 * Structure principale du système graphique
 * Contient la connexion MLX, la fenêtre et toutes les ressources visuelles
 */
typedef struct s_graphics
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_textures	textures;
}				t_graphics;

/*
** ============================================================================
** FONCTIONS D'INITIALISATION GRAPHIQUE
** ============================================================================
*/

/**
 * Initialise complètement le système de rendu graphique
 * Orchestre l'initialisation MLX, la création de fenêtre et le chargement
 * des ressources avec gestion d'erreur intégrée.
 * @param render_system Structure graphique à initialiser
 * @param level_data Données de la carte de jeu
 * @return 1 si succès, 0 si échec
 */
int				initialize_graphics_system(t_graphics *render_system,
					t_map *level_data);

/**
 * Établit la connexion avec le serveur graphique MLX
 * Initialise la connexion de base nécessaire pour toutes les opérations
 * graphiques ultérieures du système de rendu.
 * @param render_system Structure contenant les données graphiques
 * @return 1 si succès, 0 si échec
 */
int				establish_mlx_connection(t_graphics *render_system);

/**
 * Crée la fenêtre principale de l'application de jeu
 * Calcule automatiquement les dimensions selon la taille de la carte
 * et initialise la fenêtre avec le titre approprié.
 * @param render_system Structure graphique principale
 * @param level_data Données de la carte pour calculer les dimensions
 * @return 1 si succès, 0 si échec
 */
int				create_main_window(
					t_graphics *render_system, t_map *level_data);

/*
** ============================================================================
** FONCTIONS DE GESTION DES RESSOURCES
** ============================================================================
*/

/**
 * Charge toutes les ressources graphiques du jeu
 * Initialise l'ensemble des textures nécessaires au rendu incluant
 * personnage, murs, objets collectables, sol et sortie.
 * @param render_system Structure graphique contenant les textures
 * @return 1 si succès, 0 si échec
 */
int				load_game_assets(t_graphics *render_system);

/**
 * Initialise une structure graphique avec des valeurs par défaut
 * Remet à zéro tous les pointeurs et valeurs numériques pour éviter
 * les erreurs de segmentation lors des opérations ultérieures.
 * @param render_system Structure graphique à initialiser
 * @return void
 */
void			reset_graphics_structure(t_graphics *render_system);

/**
 * Libère toutes les ressources graphiques allouées
 * Détruit les textures, fenêtre et connexion MLX avec gestion
 * conditionnelle pour éviter les double-libérations.
 * @param render_system Structure graphique à nettoyer
 * @return void
 */
void			cleanup_graphics_resources(t_graphics *render_system);

/*
** ============================================================================
** FONCTIONS D'ÉTAT DE JEU
** ============================================================================
*/

/**
 * Configure l'état initial du jeu pour une nouvelle partie
 * Initialise les compteurs, position du joueur et état des collectibles
 * en préparation du lancement de la session de jeu.
 * @param game_instance Structure principale du jeu à configurer
 * @return void
 */
void			configure_initial_game_state(t_game *game_instance);

#endif
