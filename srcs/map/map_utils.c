/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:07:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 18:35:31 by abbouras         ###   ########.fr       */
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

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}

/**
 * Initialise la structure t_map avec des valeurs par défaut.
 *
 * @param map Pointeur vers la structure t_map à initialiser
 */
void	init_map(t_map *map)
{
	if (!map)
		ft_error("Erreur : Pointeur map invalide");
	map->matrix = NULL;
	map->width = 0;
	map->height = 0;
	map->total_collect = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->exit_x = -1;
	map->exit_y = -1;
}

/**
 * Compte le nombre d'occurrences d'un caractère dans la matrice.
 *
 * @param map Pointeur vers la structure t_map
 * @param c Caractère à compter
 * @return Nombre d'occurrences du caractère, -1 si erreur
 */
int	count_char(t_map *map, char c)
{
	int	count;
	int	i;
	int	j;

	if (!map || !map->matrix)
		return (-1);
	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->matrix[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

/**
 * Trouve la position d'un caractère dans la matrice.
 *
 * @param map Pointeur vers la structure t_map
 * @param c Caractère à trouver
 * @param x Pointeur pour stocker la position x
 * @param y Pointeur pour stocker la position y
 * @return 1 si trouvé, 0 si non trouvé ou erreur
 */
int	find_char_pos(t_map *map, char c, int *x, int *y)
{
	int	i;
	int	j;

	if (!map || !map->matrix || !x || !y)
		return (0);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->matrix[i][j] == c)
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Vérifie si un caractère est valide pour la carte.
 *
 * @param c Caractère à vérifier
 * @return 1 si valide, 0 sinon
 */
int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}