# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 18:42:05 by mmisskin          #+#    #+#              #
#    Updated: 2023/11/26 12:01:54 by mmisskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRC			=	mandatory/src/cub3d.c \
				mandatory/src/utils.c \
				mandatory/src/memory/free.c \
				mandatory/src/movement/movement.c \
				mandatory/src/draw/ceiling.c \
				mandatory/src/draw/floor.c \
				mandatory/src/draw/stripe.c \
				mandatory/src/rays/rays.c \
				mandatory/src/hooks/hooks.c \
				mandatory/src/hooks/hooks_utils.c \
				mandatory/src/parsing/error.c \
				mandatory/src/parsing/floor_cieling.c \
				mandatory/src/parsing/init_player.c \
				mandatory/src/parsing/load_elements.c \
				mandatory/src/parsing/map_parsing_tools.c \
				mandatory/src/parsing/map_parsing.c \
				mandatory/src/parsing/readmap.c \
				mandatory/src/parsing/parsing.c \
				mandatory/src/parsing/tools.c \
				mandatory/src/parsing/free_tools.c \
				mandatory/src/parsing/checkers.c \
				mandatory/src/parsing/len_tools.c

GNL			=	mandatory/src/gnl/get_next_line.c \
				mandatory/src/gnl/get_next_line_utils.c

LIBFT		=	mandatory/src/libft/ft_strchr.c \
				mandatory/src/libft/ft_strlen.c \
				mandatory/src/libft/ft_strrchr.c \
				mandatory/src/libft/ft_strdup.c \
				mandatory/src/libft/ft_strtrim.c \
				mandatory/src/libft/ft_putstr_fd.c \
				mandatory/src/libft/ft_putchar_fd.c \
				mandatory/src/libft/ft_putendl_fd.c \
				mandatory/src/libft/ft_split.c \
				mandatory/src/libft/ft_substr.c \
				mandatory/src/libft/ft_strcmp.c \
				mandatory/src/libft/ft_isdigit.c \
				mandatory/src/libft/ft_atoi.c 

HEADER		=	mandatory/include/cub3d.h \
				mandatory/include/get_next_line.h \
				mandatory/include/libft.h \
				mandatory/include/vectors.h \
				mandatory/include/parser.h \
				mandatory/include/player.h 

SRC_OBJ 		=	$(SRC:.c=.o)
GNL_OBJ 		=	$(GNL:.c=.o)
LIBFT_OBJ 		=	$(LIBFT:.c=.o)
CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror #-g -fsanitize=address
MLX			=	MLX42
MLX_LIB		=	$(MLX)/build/libmlx42.a
MLX_FLAGS	=	$(MLX_LIB) -lglfw -L $(HOME)/.brew/Cellar/glfw/3.3.8/lib

all:		$(MLX_LIB) $(NAME)

$(NAME):	$(SRC_OBJ) $(GNL_OBJ) $(LIBFT_OBJ)
	$(CC) $(C_FLAGS) $(MLX_FLAGS) $^ -o $@

%.o:		%.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(MLX_LIB):
	cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4

clean:
	rm -f $(SRC_OBJ) $(GNL_OBJ) $(LIBFT_OBJ)
	rm -rf $(MLX)/build

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
