/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:40:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 17:43:14 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Vérifie le contenu d'une ligne de la carte.
 * Valide la largeur et les caractères autorisés.
 *
 * @param line Ligne à vérifier
 * @param width Largeur attendue de la ligne
 * @param collect Pointeur vers le compteur de collectibles
 * @return 1 si la ligne est valide, 0 sinon
 */
int	check_line_content(char *line, int width, int *collect)
{
	int	j;

	if (!line || !collect || width <= 0)
		return (0);
	if ((int)ft_strlen(line) != width)
		return (0);
	j = 0;
	while (line[j])
	{
		if (line[j] != '0' && line[j] != '1' && 
			line[j] != 'C' && line[j] != 'E' && line[j] != 'P')
			return (0);
		if (line[j] == 'C')
			(*collect)++;
		j++;
	}
	return (1);
}

/**
 * Traite une ligne de la carte et l'ajoute à la matrice.
 * Définit la largeur de la carte si c'est la première ligne.
 *
 * @param map Structure de la carte
 * @param line Ligne à traiter
 * @param i Index de la ligne dans la matrice
 * @return 1 si succès, 0 si échec
 */
int	process_line(t_map *map, char *line, int i)
{
	if (!map || !line || i < 0)
		return (0);
	if (i == 0)
	{
		map->width = ft_strlen(line);
		if (map->width <= 0)
			return (0);
	}
	if (!check_line_content(line, map->width, &map->total_collect))
	{
		free_matrix(map->matrix, i + 1);
		return (0);
	}
	map->matrix[i] = line;
	return (1);
}

/**
 * Initialise la lecture de la carte.
 * Vérifie l'extension, ouvre le fichier et compte les lignes.
 *
 * @param path Chemin du fichier de carte
 * @param fd Pointeur vers le descripteur de fichier
 * @param lines Pointeur vers le nombre de lignes
 * @return 1 si succès, 0 si échec
 */
int	init_map_reading(const char *path, int *fd, int *lines)
{
	if (!path || !fd || !lines)
		return (0);
	if (!has_ber_extension(path))
		ft_error("Invalid map extension (must be .ber)");
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		ft_error("Failed to open map file");
	*lines = count_lines(*fd);
	if (*lines <= 0)
	{
		close(*fd);
		ft_error("Empty or invalid map file");
	}
	return (1);
} 