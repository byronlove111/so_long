/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:43:35 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 16:34:15 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_error("Usage : %s <fichier.ber>\n");
	else if (has_ber_extension(argv[1]))
		ft_printf("Extension .ber valide pour %s\n", argv[1]);
	else
		ft_error("Erreur : le fichier ne se termine pas par .ber\n");
	return (0);
}
