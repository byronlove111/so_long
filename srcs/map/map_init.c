/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:01:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 18:01:50 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * Compte le nombre de lignes dans le fichier.
 *
 * @param fd File descriptor du fichier
 * @return Nombre de lignes, -1 si erreur
 */
static int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	return (count);
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
	if (height <= 0)
		return (0);
	map->matrix = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map->matrix)
		return (0);
	map->height = height;
	map->matrix[height] = NULL;
	return (1);
}

/**
 * Initialise la lecture de la carte et compte les lignes.
 *
 * @param path Chemin vers le fichier
 * @param map Pointeur vers la structure t_map
 * @return Nombre de lignes dans le fichier
 */
int	init_map_reading(const char *path, t_map *map)
{
	int	fd;
	int	lines;

	if (!has_ber_extension(path))
		ft_error("Erreur : Extension de fichier invalide");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Erreur : Impossible d'ouvrir le fichier");
	lines = count_lines(fd);
	if (lines <= 0)
	{
		close(fd);
		ft_error("Erreur : Fichier vide ou invalide");
	}
	close(fd);
	if (!allocate_matrix(map, lines))
		ft_error("Erreur : Allocation mémoire échouée");
	return (lines);
} 