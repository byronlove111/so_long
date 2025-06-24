/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:34 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 05:21:24 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** ============================================================================
** DÉCLARATION FORWARD POUR ÉVITER LES DÉPENDANCES CIRCULAIRES
** ============================================================================
*/
typedef struct s_game	t_game;

/*
** ============================================================================
** FONCTIONS DE GESTION MÉMOIRE
** ============================================================================
*/

/**
 * Libère un tableau de chaînes de caractères alloué dynamiquement
 * Parcourt chaque élément du tableau pour libérer individuellement
 * chaque chaîne avant de libérer le tableau lui-même.
 * @param string_array Tableau de chaînes à libérer
 * @return void
 */
void	deallocate_string_array(char **string_array);

/*
** ============================================================================
** FONCTIONS DE GESTION DU PROGRAMME
** ============================================================================
*/

/**
 * Termine proprement l'application de jeu avec nettoyage complet
 * Libère toutes les ressources allouées incluant la carte, les graphiques
 * et la structure principale avant de quitter le programme.
 * @param game_instance Structure principale du jeu à nettoyer
 * @return void (fonction ne retourne jamais)
 */
void	terminate_game_application(t_game *game_instance);

/*
** ============================================================================
** FONCTIONS UTILITAIRES DE DEBUG
** ============================================================================
*/

/**
 * Affiche un tableau de chaînes sur un descripteur de fichier
 * Fonction utilitaire pour le débogage et l'affichage de structures
 * de données complexes lors du développement.
 * @param arr Tableau de chaînes à afficher
 * @param fd Descripteur de fichier de destination
 * @return void
 */
void	print_str_array(char **arr, int fd);

#endif
