/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 04:45:32 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Affiche un message d'erreur spécifique selon le code d'erreur de validation.
 * Traduit les codes d'erreur numériques en messages explicites
 * pour informer l'utilisateur du problème détecté dans la carte.
 * @param error_type Code numérique représentant le type d'erreur
 * @return void
 */
void	display_validation_error(int error_type)
{
	if (error_type == ERR_NO_PLAYER)
		ft_putstr_fd("Error\nMap must have exactly one starting point (P)\n",
			2);
	else if (error_type == ERR_MULTI_PLAYER)
		ft_putstr_fd("Error\nMap has multiple starting points\n", 2);
	else if (error_type == ERR_NO_EXIT)
		ft_putstr_fd("Error\nMap must have exactly one exit (E)\n", 2);
	else if (error_type == ERR_MULTI_EXIT)
		ft_putstr_fd("Error\nMap has multiple exits\n", 2);
	else if (error_type == ERR_NO_COLLECT)
		ft_putstr_fd("Error\nMap must have at least one collectible (C)\n", 2);
	else if (error_type == ERR_INVALID_CHAR)
		ft_putstr_fd("Error\nMap contains invalid character\n", 2);
	else if (error_type == ERR_NOT_RECTANGLE)
		ft_putstr_fd("Error\nMap must be rectangular\n", 2);
	else if (error_type == ERR_NO_WALLS)
		ft_putstr_fd("Error\nMap must be surrounded by walls\n", 2);
	else if (error_type == ERR_MAP_TOO_SMALL)
		ft_putstr_fd("Error\nMap is too small\n", 2);
	else if (error_type == ERR_MEMORY)
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
	else if (error_type == ERR_NO_PATH)
		ft_putstr_fd("Error\nMap has no valid path\n", 2);
} 
