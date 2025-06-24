NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Libft paths
LIBFT_DIR = external/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Détection automatique du système d'exploitation
UNAME = $(shell uname)

# minilibx paths - Adaptation pour macOS et Linux
ifeq ($(UNAME), Darwin)
MLX_DIR = external/minilibx_mms_20200219
MLX = $(MLX_DIR)/libmlx.dylib
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_COPY = cp $(MLX) .
else
# Pour Linux (au cas où)
MLX_DIR = external/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm -lz -L/usr/lib -L/usr/X11R6/lib
MLX_COPY = # Pas besoin de copier pour Linux
endif

# Headers
INCLUDES = -I./include -I$(LIBFT_DIR) -I$(MLX_DIR)

# Source files - nouvelle architecture avec modules de rendu refactorisés
SRCS =  src/main.c \
        src/engine/game_setup.c \
        src/engine/system_manager.c \
        src/render/graphics_initialization.c \
        src/render/texture_asset_loader.c \
        src/render/memory_cleanup_manager.c \
        src/render/game_state_initializer.c \
        src/map/map_file_handler.c \
        src/map/map_structure_validator.c \
        src/map/map_element_validator.c \
        src/map/map_connectivity_analyzer.c \
        src/map/map_connectivity_validator.c \
        src/map/map_error_manager.c \
        src/map/map_render_engine.c \
        src/map/map_main_validator.c \
        src/player/player_controller.c \
        src/utils/resource_manager.c

OBJS = $(SRCS:.c=.o)

# Règles
all: $(NAME)

# Compilation de libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compilation de minilibx
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Compilation du projet principal
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
	$(MLX_COPY)

# Règle pour les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	$(RM) $(OBJS)
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
