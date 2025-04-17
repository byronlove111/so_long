/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:43:35 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 19:36:46 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <string.h>

int	main(int argc, char **argv)
{
	t_map map;

	if (argc != 2)
		ft_error("Usage : %s <chemin vers .ber> ou 'test'\n");
	if (strcmp(argv[1], "test") == 0)
	{
		char	*map_files[] = {
			"maps/42.ber",
			// "maps/badcols.ber",
			"maps/badwall.ber",
			"maps/big.ber",
			"maps/large.ber",
			"maps/nocollectible.ber",
			"maps/noexit.ber",
			"maps/noplayer.ber",
			"maps/simple.ber",
			"maps/tiny.ber",
			"maps/tooplayer.ber",
			NULL
		};
		int	i = 0;

		while (map_files[i])
		{
			ft_printf("Test de la carte : %s\n", map_files[i]);
			init_map(&map);
			parse_map(map_files[i], &map);
			validate_map(&map);
			ft_printf("La carte %s est valide.\n", map_files[i]);
			free_matrix(map.matrix);
			i++;
		}
	}
	else if (has_ber_extension(argv[1]))
		ft_printf("Extension .ber valide pour %s\n", argv[1]);
	else
		ft_error("Erreur : le fichier ne se termine pas par .ber\n");
	return (0);
}
