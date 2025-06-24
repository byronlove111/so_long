/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/06/23 04:45:36 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Vérifie si l'extension du fichier de niveau est valide (.ber).
 * Analyse le nom de fichier pour s'assurer qu'il se termine par .ber
 * et respecte le format attendu pour les cartes de jeu.
 * @param level_filename Nom du fichier à vérifier
 * @return 1 si l'extension est valide, 0 sinon
 */
static int	verify_level_extension(char *level_filename)
{
	char	*extension_ptr;

	if (!level_filename)
		return (0);
	extension_ptr = ft_strrchr(level_filename, '.');
	if (!extension_ptr)
		return (0);
	if (ft_strlen(extension_ptr) != 4)
		return (0);
	if (ft_strncmp(extension_ptr, ".ber", 4) != 0)
		return (0);
	return (1);
}

/**
 * Compte le nombre total de lignes dans un fichier de niveau.
 * Ouvre le fichier, lit chaque ligne et maintient un compteur
 * pour déterminer la hauteur de la carte de jeu.
 * @param level_filename Chemin vers le fichier de niveau
 * @return Nombre de lignes ou -1 en cas d'erreur
 */
static int	calculate_level_height(char *level_filename)
{
	int		file_descriptor;
	int		total_rows;
	char	*current_line;

	file_descriptor = open(level_filename, O_RDONLY);
	if (file_descriptor < 0)
		return (-1);
	total_rows = 0;
	current_line = get_next_line(file_descriptor);
	while (current_line != NULL)
	{
		total_rows++;
		free(current_line);
		current_line = get_next_line(file_descriptor);
	}
	close(file_descriptor);
	return (total_rows);
}

/**
 * Calcule la largeur effective d'une ligne en excluant le caractère de fin.
 * Traite les lignes de texte pour obtenir leur longueur réelle
 * sans compter le caractère de nouvelle ligne.
 * @param text_line Ligne de texte à mesurer
 * @return Largeur de la ligne sans le caractère de fin
 */
size_t	calculate_row_width(char *text_line)
{
	size_t	character_count;

	if (!text_line)
		return (0);
	character_count = ft_strlen(text_line);
	if (character_count > 0 && text_line[character_count - 1] == '\n')
		return (character_count - 1);
	return (character_count);
}

/**
 * Gère les vérifications préliminaires et initialise la structure de carte.
 * Valide l'extension du fichier, calcule les dimensions et alloue
 * la mémoire nécessaire pour stocker les données de niveau.
 * @param level_data Structure de carte à initialiser
 * @param level_filename Chemin vers le fichier de niveau
 * @return 1 en cas de succès, 0 en cas d'erreur
 */
static int	prepare_level_structure(t_map *level_data, char *level_filename)
{
	if (!verify_level_extension(level_filename))
		return (ft_putstr_fd("Error\nInvalid file extension. Must be .ber", 2),
			0);
	level_data->height = calculate_level_height(level_filename);
	if (level_data->height <= 0)
		return (ft_putstr_fd("Error\nMemory allocation failed", 2), 0);
	level_data->map = malloc(sizeof(char *) * (level_data->height + 1));
	if (!level_data->map)
		return (ft_putstr_fd("Error\nMemory allocation failed", 2), 0);
	return (1);
}

/**
 * Charge complètement un niveau de jeu depuis un fichier .ber.
 * Orchestre le processus de chargement incluant la validation,
 * l'allocation mémoire et la lecture des données de carte.
 * @param level_data Structure de carte à remplir
 * @param level_filename Chemin vers le fichier de niveau à charger
 * @return 1 en cas de chargement réussi, 0 en cas d'échec
 */
int	load_game_level(t_map *level_data, char *level_filename)
{
	int		file_descriptor;
	int		row_index;
	char	*current_line;

	if (!prepare_level_structure(level_data, level_filename))
		return (0);
	file_descriptor = open(level_filename, O_RDONLY);
	if (file_descriptor < 0)
		return (ft_putstr_fd("Error\nFailed to open map file", 2), 0);
	row_index = 0;
	current_line = get_next_line(file_descriptor);
	while (current_line != NULL)
	{
		level_data->map[row_index] = current_line;
		if (row_index == 0)
			level_data->width = calculate_row_width(current_line);
		row_index++;
		current_line = get_next_line(file_descriptor);
	}
	level_data->map[row_index] = NULL;
	close(file_descriptor);
	return (1);
}
