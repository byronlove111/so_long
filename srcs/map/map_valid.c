/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:07:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 19:32:11 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Crée une copie de la matrice pour la validation du chemin.
 *
 * @param map Pointeur vers la structure t_map
 * @return Copie de la matrice ou NULL si échec
 */
static char	**copy_matrix(t_map *map)
{
	char	**copy;
	int		i;

	if (!map || !map->matrix)
		return (NULL);
	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->matrix[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[map->height] = NULL;
	return (copy);
}

/**
 * Vérifie récursivement si un chemin existe vers tous les objectifs.
 *
 * @param map_copy Copie de la matrice pour le flood fill
 * @param x Position x courante
 * @param y Position y courante
 * @param ctx Pointeur vers le contexte du flood fill
 * @return 1 si un chemin existe, 0 sinon
 */
int	flood_fill(char **map_copy, int x, int y, t_flood_context *ctx)
{
	int	h;
	int	w;

	if (!map_copy)
		return (0);
		h = 0;
		while (map_copy[h])
			h++;
		if (h == 0)
			return (0);
		w = ft_strlen(map_copy[0]);
		if (x < 0 || y < 0 || x >= w || y >= h)
			return (0);
		if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
			return (0);
		if (map_copy[y][x] == 'C')
			ctx->collectibles++;
		if (map_copy[y][x] == 'E')
			ctx->exit_found = 1;
		map_copy[y][x] = 'V';
		flood_fill(map_copy, x + 1, y, ctx);
		flood_fill(map_copy, x - 1, y, ctx);
		flood_fill(map_copy, x, y + 1, ctx);
		flood_fill(map_copy, x, y - 1, ctx);
		return (ctx->collectibles == ctx->total_collect && ctx->exit_found);
}

/**
 * Vérifie si la carte est jouable (chemin valide vers collectibles et sortie).
 *
 * @param map Pointeur vers la structure t_map
 * @return 1 si jouable, 0 sinon
 */
static int	is_map_playable(t_map *map)
{
	char			**map_copy;
	int				player_x;
	int				player_y;
	int				result;
	t_flood_context	ctx;

	if (!map || !map->matrix)
		return (0);
	if (!find_char_pos(map, 'P', &player_x, &player_y))
		return (0);
	map_copy = copy_matrix(map);
	if (!map_copy)
		return (0);
	ctx.collectibles = 0;
	ctx.exit_found = 0;
	ctx.total_collect = map->total_collect;
	result = flood_fill(map_copy, player_x, player_y, &ctx);
	free_matrix(map_copy);
	return (result);
}

/**
 * Valide la carte en effectuant toutes les vérifications nécessaires.
 *
 * @param map Pointeur vers la structure t_map
 */
void	validate_map(t_map *map)
{
	if (!map || !map->matrix)
		ft_error("Erreur : Carte invalide ou non initialisée");
	check_rectangular(map);
	check_walls_closed(map);
	check_elements(map);
	if (!is_map_playable(map))
		ft_error("Erreur : Carte impossible à terminer");
}
