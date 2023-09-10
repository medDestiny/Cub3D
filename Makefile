# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 18:42:05 by mmisskin          #+#    #+#              #
#    Updated: 2023/09/10 19:06:39 by mmisskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
SRC			=	test.c
OBJ 		=	$(SRC:.c=.o)
HEADER		=
CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror
MLX			=	MLX42
MLX_LIB		=	$(MLX)/build/libmlx42.a
MLX_FLAGS	=	$(MLX_LIB) -lglfw -L $(HOME)/.brew/Cellar/glfw/3.3.8/lib

all:		$(MLX_LIB) $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(C_FLAGS) $(MLX_FLAGS) $< -o $@

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
