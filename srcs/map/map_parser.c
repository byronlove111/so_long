/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:07:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 17:57:46 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Vérifie si le chemin du fichier se termine par l'extension ".ber".
 *
 * @param path Chemin du fichier à vérifier.
 * @return 1 si l'extension est ".ber", 0 sinon.
 */
int	has_ber_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".ber", 4) == 0)
		return (1);
	return (0);
}

/**
 * Compte le nombre de lignes dans le fichier de carte.
 *
 * @param fd File descriptor du fichier de carte
 * @return Nombre de lignes dans le fichier
 */
static int	count_lines(int fd)
{
	int		lines;
	char	*line;
	int		ret;

	if (fd < 0)
		return (-1);
	lines = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		lines++;
		free(line);
	}
	if (ret < 0)
		ft_error("Error reading map file");
	if (line)
		free(line);
	return (lines);
}

/**
 * Alloue la mémoire pour la matrice de la carte.
 *
 * @param map Pointeur vers la structure t_map
 * @param height Nombre de lignes à allouer
 * @return 1 si succès, 0 si échec
 */
static int	allocate_matrix(t_map *map, int height)
{
	if (!map || height <= 0)
		return (0);
	map->height = height;
	map->matrix = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map->matrix)
		return (0);
	map->matrix[height] = NULL;
	map->total_collect = 0;
	return (1);
}

/**
 * Remplit la matrice avec le contenu du fichier de carte.
 *
 * @param fd File descriptor du fichier de carte
 * @param map Pointeur vers la structure t_map
 * @return 1 si succès, 0 si échec
 */
static int	fill_matrix(int fd, t_map *map)
{
	int		i;
	char	*line;

	if (fd < 0 || !map || !map->matrix)
		return (0);
	i = 0;
	while (i < map->height && get_next_line(fd, &line) > 0)
	{
		if (!line || !process_line(map, line, i))
		{
			if (line)
				free(line);
			free_matrix(map->matrix, i);
			return (0);
		}
		i++;
	}
	if (i != map->height)
	{
		free_matrix(map->matrix, i);
		return (0);
	}
	return (1);
}

/**
 * Lit le fichier .ber et initialise la structure t_map.
 *
 * @param path Chemin vers le fichier de carte (.ber)
 * @param map  Pointeur vers la structure t_map à remplir
 *
 * La structure t_map contient :
 * - matrix        : tableau de chaînes représentant la carte
 * - width         : nombre de colonnes
 * - height        : nombre de lignes
 * - total_collect : nombre total de collectibles ('C')
 */
void	parse_map(const char *path, t_map *map)
{
	int	fd;
	int	lines;

	if (!path || !map)
		ft_error("Invalid parameters for parse_map");
	if (!init_map_reading(path, &fd, &lines))
		return ;
	close(fd);
	if (!allocate_matrix(map, lines))
		ft_error("Failed to allocate map matrix");
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(map->matrix);
		ft_error("Failed to open map file");
	}
	if (!fill_matrix(fd, map))
	{
		close(fd);
		ft_error("Invalid map content");
	}
	close(fd);
}
