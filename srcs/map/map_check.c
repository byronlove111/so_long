/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:07:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 17:54:24 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Vérifie si les caractères de la carte sont valides.
 *
 * @param map Pointeur vers la structure t_map
 * @return 1 si valide, 0 sinon
 */
static int	check_valid_chars(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->matrix)
		return (0);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->matrix[i][j] != '0' && map->matrix[i][j] != '1'
				&& map->matrix[i][j] != 'C' && map->matrix[i][j] != 'E'
				&& map->matrix[i][j] != 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * Vérifie si la carte est rectangulaire.
 *
 * @param map Pointeur vers la structure t_map
 */
void	check_rectangular(t_map *map)
{
	int	i;
	size_t	len;

	if (!map || !map->matrix || map->height < 3)
		ft_error("Erreur : Carte invalide (trop petite ou vide)");
	len = ft_strlen(map->matrix[0]);
	if (len < 3)
		ft_error("Erreur : Carte invalide (trop étroite)");
	i = 1;
	while (i < map->height)
	{
		if (ft_strlen(map->matrix[i]) != len)
			ft_error("Erreur : Carte non rectangulaire");
		i++;
	}
	map->width = len;
	if (!check_valid_chars(map))
		ft_error("Erreur : Caractères invalides dans la carte");
}

/**
 * Vérifie si la carte est entourée de murs.
 *
 * @param map Pointeur vers la structure t_map
 */
void	check_walls_closed(t_map *map)
{
	int	i;

	if (!map || !map->matrix)
		ft_error("Erreur : Carte invalide");
	i = 0;
	while (i < map->width)
	{
		if (map->matrix[0][i] != '1' || map->matrix[map->height - 1][i] != '1')
			ft_error("Erreur : Murs non fermés");
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->matrix[i][0] != '1' || map->matrix[i][map->width - 1] != '1')
			ft_error("Erreur : Murs non fermés");
		i++;
	}
}

/**
 * Vérifie si la carte contient tous les éléments requis (P, E, C).
 *
 * @param map Pointeur vers la structure t_map
 */
void	check_elements(t_map *map)
{
	int	player;
	int	exit;
	int	collect;

	if (!map || !map->matrix)
		ft_error("Erreur : Carte invalide");
	player = count_char(map, 'P');
	exit = count_char(map, 'E');
	collect = count_char(map, 'C');
	if (player != 1)
		ft_error("Erreur : Nombre de joueurs incorrect");
	if (exit != 1)
		ft_error("Erreur : Nombre de sorties incorrect");
	if (collect < 1)
		ft_error("Erreur : Pas de collectibles");
	map->total_collect = collect;
}
