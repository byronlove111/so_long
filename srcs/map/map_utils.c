/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:07:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 17:32:32 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Libère la mémoire allouée pour la matrice de la carte.
 *
 * @param matrix Tableau de chaînes à libérer
 */
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	return ;
}

/**
 * Initialise la structure t_map avec des valeurs par défaut.
 *
 * @param map Pointeur vers la structure t_map à initialiser
 */
void	init_map(t_map *map)
{
	map->matrix = NULL;
	map->width = 0;
	map->height = 0;
	map->total_collect = 0;
	return ;
}

/**
 * Compte le nombre d'occurrences d'un caractère dans la matrice.
 *
 * @param map Pointeur vers la structure t_map
 * @param c Caractère à compter
 * @return Nombre d'occurrences du caractère
 */
int	count_char(t_map *map, char c)
{
	return ;
}

/**
 * Trouve la position d'un caractère dans la matrice.
 *
 * @param map Pointeur vers la structure t_map
 * @param c Caractère à trouver
 * @param x Pointeur pour stocker la position x
 * @param y Pointeur pour stocker la position y
 * @return 1 si trouvé, 0 sinon
 */
int	find_char_pos(t_map *map, char c, int *x, int *y)
{
	return ;
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}