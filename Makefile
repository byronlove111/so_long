# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 15:26:12 by abbouras          #+#    #+#              #
#    Updated: 2025/04/17 15:39:43 by abbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Libft paths
LIBFT_DIR = external/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Détection automatique du système d'exploitation
UNAME = $(shell uname)

# minilibx paths - Commentez/décommentez selon votre système
# Pour basculer entre macOS et Linux, commentez/décommentez les sections correspondantes

# Pour macOS
ifeq ($(UNAME), Darwin)
MLX_DIR = external/minilibx_mms_20200219
MLX = $(MLX_DIR)/libmlx.dylib
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_COPY = cp $(MLX) .
else
# Pour Linux
MLX_DIR = external/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm -lz
MLX_COPY = # Pas besoin de copier pour Linux
endif

# Headers
INCLUDES = -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)

# Source files
SRC_DIR = srcs
SRC_FILES = main.c \
           events/exit.c events/hooks.c events/keyboard.c \
           gameplay/collect.c gameplay/game_state.c gameplay/movement.c gameplay/player.c \
           graphics/init.c graphics/render.c graphics/textures.c graphics/window.c \
           map/map_check.c map/map_parser.c map/map_utils.c map/map_valid.c \
           utils/debug.c utils/error.c utils/memory.c
           
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

# Règles
all: $(NAME)

# Compilation de libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compilation de minilibx
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Compilation du projet principal
$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) $(MLX_FLAGS)
	$(MLX_COPY)

# Règle pour les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Nettoyage des fichiers objets et de l'exécutable
fclean: clean
	$(RM) $(NAME)
	$(RM) libmlx.dylib
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re
