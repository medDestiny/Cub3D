# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 18:42:05 by mmisskin          #+#    #+#              #
#    Updated: 2023/11/24 11:57:08 by mmisskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRC			=	src/cub3d.c \
				src/map.c \
				src/draw.c \
				src/utils.c \
				src/movement.c \
				src/ai.c \
				src/rays.c \
				src/free.c \
				src/parsing/error.c \
				src/parsing/floor_cieling.c \
				src/parsing/init_player.c \
				src/parsing/load_elements.c \
				src/parsing/map_parsing_tools.c \
				src/parsing/map_parsing.c \
				src/parsing/readmap.c \
				src/parsing/parsing.c \
				src/parsing/tools.c \
				src/parsing/free_tools.c \
				src/parsing/checkers.c \
				src/parsing/len_tools.c \

GNL			=	src/gnl/get_next_line.c \
				src/gnl/get_next_line_utils.c

LIBFT		=	src/libft/ft_strchr.c \
				src/libft/ft_strdup.c \
				src/libft/ft_strlen.c \
				src/libft/ft_strrchr.c \
				src/libft/ft_strtrim.c \
				src/libft/ft_putstr_fd.c \
				src/libft/ft_split.c \
				src/libft/ft_substr.c \
				src/libft/ft_calloc.c \
				src/libft/ft_strcmp.c \
				src/libft/ft_bzero.c \
				src/libft/ft_isdigit.c \
				src/libft/ft_atoi.c 

HEADER		=	include/cub3d.h \
				include/get_next_line.h \
				include/libft.h \
				include/vectors.h \
				include/astar.h \
				include/parser.h \
				include/sprite.h \
				include/player.h \
				include/map.h

OBJ 		=	$(SRC:.c=.o)
OBJ 		+=	$(GNL:.c=.o)
OBJ 		+=	$(LIBFT:.c=.o)
CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address
MLX			=	MLX42
MLX_LIB		=	$(MLX)/build/libmlx42.a
MLX_FLAGS	=	$(MLX_LIB) -lglfw -L $(HOME)/.brew/Cellar/glfw/3.3.8/lib

all:		$(MLX_LIB) $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(C_FLAGS) $(MLX_FLAGS) $^ -o $@

%.o:		%.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(MLX_LIB):
	cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4

clean:
	rm -f $(OBJ)
	rm -rf $(MLX)/build

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
