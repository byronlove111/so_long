/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:45:18 by abbouras          #+#    #+#             */
/*   Updated: 2025/04/17 16:28:44 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../external/libft/libft.h"
# include "utils.h"
# include "../external/minilibx_mms_20200219/mlx.h"
# include "map.h"
# include "gameplay.h"
# include "graphics.h"

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
    t_map      map;
    t_player   player;
    t_graphic  gfx;
}  t_game;

#endif
