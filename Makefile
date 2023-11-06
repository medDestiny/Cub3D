# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 18:42:05 by mmisskin          #+#    #+#              #
#    Updated: 2023/11/06 15:08:29 by mmisskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRC			=	src/cub3d.c \
				src/map.c \
				src/draw.c \
				src/utils.c \
				src/rays.c

GNL			=	src/gnl/get_next_line.c \
				src/gnl/get_next_line_utils.c

LIBFT		=	src/libft/ft_strchr.c \
				src/libft/ft_strdup.c \
				src/libft/ft_strlen.c \
				src/libft/ft_strrchr.c \
				src/libft/ft_strtrim.c

HEADER		=	include/cub3d.h \
				include/get_next_line.h \
				include/libft.h \
				include/map.h

OBJ 		=	$(SRC:.c=.o)
OBJ 		+=	$(GNL:.c=.o)
OBJ 		+=	$(LIBFT:.c=.o)
CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
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
