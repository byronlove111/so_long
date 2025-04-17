/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:07:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 18:01:40 by abbouras         ###   ########.fr       */
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
 * Remplit la matrice avec le contenu du fichier.
 *
 * @param fd File descriptor du fichier
 * @param map Pointeur vers la structure t_map
 * @return 1 si succès, 0 si échec
 */
static int	fill_matrix(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free_matrix(map->matrix);
			return (0);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map->matrix[i] = ft_strdup(line);
		free(line);
		if (!map->matrix[i])
		{
			free_matrix(map->matrix);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * Lit le fichier .ber et initialise la structure t_map.
 *
 * @param path Chemin vers le fichier de carte (.ber)
 * @param map Pointeur vers la structure t_map à remplir
 */
void	parse_map(const char *path, t_map *map)
{
	int	fd;

	init_map_reading(path, map);
	fd = open(path, O_RDONLY);
	if (fd == -1 || !fill_matrix(fd, map))
	{
		if (fd != -1)
			close(fd);
		free_matrix(map->matrix);
		ft_error("Erreur : Lecture du fichier échouée");
	}
	close(fd);
}