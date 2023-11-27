# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 18:42:05 by mmisskin          #+#    #+#              #
#    Updated: 2023/11/27 12:58:26 by anchaouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
BNAME			=	cub3D_bonus

MANDATORY		=	mandatory

BONUS			=	bonus

SRC				=	MANDATORY/src/cub3d.c \
					MANDATORY/src/utils.c \
					MANDATORY/src/memory/free.c \
					MANDATORY/src/movement/movement.c \
					MANDATORY/src/draw/ceiling.c \
					MANDATORY/src/draw/floor.c \
					MANDATORY/src/draw/stripe.c \
					MANDATORY/src/rays/rays.c \
					MANDATORY/src/hooks/hooks.c \
					MANDATORY/src/hooks/hooks_utils.c \
					MANDATORY/src/parsing/error.c \
					MANDATORY/src/parsing/floor_cieling.c \
					MANDATORY/src/parsing/init_player.c \
					MANDATORY/src/parsing/load_elements.c \
					MANDATORY/src/parsing/map_parsing_tools.c \
					MANDATORY/src/parsing/map_parsing.c \
					MANDATORY/src/parsing/readmap.c \
					MANDATORY/src/parsing/parsing.c \
					MANDATORY/src/parsing/tools.c \
					MANDATORY/src/parsing/free_tools.c \
					MANDATORY/src/parsing/checkers.c \
					MANDATORY/src/parsing/len_tools.c

GNL				=	MANDATORY/src/gnl/get_next_line.c \
					MANDATORY/src/gnl/get_next_line_utils.c

LIBFT			=	MANDATORY/src/libft/ft_strchr.c \
					MANDATORY/src/libft/ft_strlen.c \
					MANDATORY/src/libft/ft_strrchr.c \
					MANDATORY/src/libft/ft_strdup.c \
					MANDATORY/src/libft/ft_strtrim.c \
					MANDATORY/src/libft/ft_putstr_fd.c \
					MANDATORY/src/libft/ft_putchar_fd.c \
					MANDATORY/src/libft/ft_putendl_fd.c \
					MANDATORY/src/libft/ft_split.c \
					MANDATORY/src/libft/ft_substr.c \
					MANDATORY/src/libft/ft_strcmp.c \
					MANDATORY/src/libft/ft_isdigit.c \
					MANDATORY/src/libft/ft_atoi.c 

HEADER			=	MANDATORY/include/cub3d.h \
					MANDATORY/include/get_next_line.h \
					MANDATORY/include/libft.h \
					MANDATORY/include/vectors.h \
					MANDATORY/include/parser.h \
					MANDATORY/include/player.h 

B_SRC			=	BONUS/src/cub3d.c \
					BONUS/src/utils.c \
					BONUS/src/ai/ai.c \
					BONUS/src/ai/astar_list.c \
					BONUS/src/ai/init_astar.c \
					BONUS/src/draw/ceiling.c \
					BONUS/src/draw/draw.c \
					BONUS/src/draw/floor.c \
					BONUS/src/draw/hud.c \
					BONUS/src/draw/sprite.c \
					BONUS/src/draw/sprite_utils.c \
					BONUS/src/draw/stripe.c \
					BONUS/src/hooks/hooks.c \
					BONUS/src/memory/free.c \
					BONUS/src/movement/movement.c \
					BONUS/src/rays/rays.c \
					BONUS/src/parsing/checkers.c \
					BONUS/src/parsing/error.c \
					BONUS/src/parsing/floor_cieling.c \
					BONUS/src/parsing/free_tools.c \
					BONUS/src/parsing/init_player.c \
					BONUS/src/parsing/len_tools.c \
					BONUS/src/parsing/load_elements.c \
					BONUS/src/parsing/map_parsing.c \
					BONUS/src/parsing/map_parsing_tools.c \
					BONUS/src/parsing/parsing.c \
					BONUS/src/parsing/readmap.c \
					BONUS/src/parsing/tools.c

B_GNL			=	BONUS/src/gnl/get_next_line.c \
					BONUS/src/gnl/get_next_line_utils.c

B_LIBFT			=	BONUS/src/libft/ft_atoi.c \
					BONUS/src/libft/ft_isdigit.c \
					BONUS/src/libft/ft_putchar_fd.c \
					BONUS/src/libft/ft_putendl_fd.c \
					BONUS/src/libft/ft_putstr_fd.c \
					BONUS/src/libft/ft_split.c \
					BONUS/src/libft/ft_strchr.c \
					BONUS/src/libft/ft_strcmp.c \
					BONUS/src/libft/ft_strdup.c \
					BONUS/src/libft/ft_strlen.c \
					BONUS/src/libft/ft_strrchr.c \
					BONUS/src/libft/ft_strtrim.c \
					BONUS/src/libft/ft_substr.c

B_HEADER		=	BONUS/include/astar.h \
					BONUS/include/cub3d.h \
					BONUS/include/get_next_line.h \
					BONUS/include/libft.h \
					BONUS/include/parser.h \
					BONUS/include/player.h \
					BONUS/include/sprite.h \
					BONUS/include/vectors.h

SRC_OBJ 		=	$(SRC:.c=.o)
GNL_OBJ 		=	$(GNL:.c=.o)
LIBFT_OBJ 		=	$(LIBFT:.c=.o)

B_SRC_OBJ 		=	$(B_SRC:.c=.o)
B_GNL_OBJ 		=	$(B_GNL:.c=.o)
B_LIBFT_OBJ 	=	$(B_LIBFT:.c=.o)

CC				=	cc
C_FLAGS			=	-Wall -Wextra -Werror #-g -fsanitize=address
MLX				=	MLX42
MLX_LIB			=	$(MLX)/build/libmlx42.a
MLX_FLAGS		=	$(MLX_LIB) -lglfw -L $(HOME)/.brew/Cellar/glfw/3.3.8/lib

all:		$(MLX_LIB) $(NAME)

bonus:		$(MLX_LIB) $(BNAME)

$(NAME):	$(SRC_OBJ) $(GNL_OBJ) $(LIBFT_OBJ)
	$(CC) $(C_FLAGS) $(MLX_FLAGS) $^ -o $@

$(BNAME):	$(B_SRC_OBJ) $(B_GNL_OBJ) $(B_LIBFT_OBJ)
	$(CC) $(C_FLAGS) $(MLX_FLAGS) $^ -o $@

MANDATORY/%.o:		MANDATORY/%.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

BONUS/%.o:		BONUS/%.c $(B_HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(MLX_LIB):
	cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4

clean:
	rm -f $(B_SRC_OBJ) $(B_GNL_OBJ) $(B_LIBFT_OBJ)
	rm -f $(SRC_OBJ) $(GNL_OBJ) $(LIBFT_OBJ)
	rm -rf $(MLX)/build

fclean:		clean
	rm -f $(NAME)
	rm -f $(BNAME)

re:			fclean all

.PHONY:		all clean fclean re
