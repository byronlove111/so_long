/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:50:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 19:22:13 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Crée une copie de la carte pour le flood fill.
 *
 * @param map Pointeur vers la structure t_map
 * @return Copie de la matrice ou NULL si erreur
 */
static char	**create_temp_map(t_map *map)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		temp_map[i] = ft_strdup(map->matrix[i]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (NULL);
		}
		i++;
	}
	temp_map[map->height] = NULL;
	return (temp_map);
}

/**
 * Vérifie si la position de départ est valide.
 *
 * @param map Pointeur vers la structure t_map
 * @param x Position x à vérifier
 * @param y Position y à vérifier
 * @return 1 si valide, 0 sinon
 */
static int	is_valid_position(t_map *map, int x, int y)
{
	if (!map || !map->matrix)
		return (0);
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	return (1);
}

/**
 * Vérifie si un chemin valide existe vers tous les collectibles et la sortie.
 *
 * @param map Pointeur vers la structure t_map
 * @param start_x Position x de départ du joueur
 * @param start_y Position y de départ du joueur
 */
void	check_path(t_map *map, int start_x, int start_y)
{
	char			**temp_map;
	t_flood_context	ctx;

	if (!is_valid_position(map, start_x, start_y))
		ft_error("Erreur : Position de départ invalide");
	temp_map = create_temp_map(map);
	if (!temp_map)
		ft_error("Erreur : Allocation mémoire échouée");
	ctx.collectibles = 0;
	ctx.exit_found = 0;
	ctx.total_collect = map->total_collect;
	if (!flood_fill(temp_map, start_x, start_y, &ctx))
	{
		free_matrix(temp_map);
		ft_error("Erreur : Pas de chemin valide");
	}
	free_matrix(temp_map);
} 
