# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 14:07:34 by hanjkim           #+#    #+#              #
#    Updated: 2025/04/30 13:46:39 by oohnivch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	=	cub3D

CC			=	cc
# CFLAGS  	=	-Wall -Werror -Wextra -g
CFLAGS  	=	-g

ifeq ($(shell uname), Linux)
		INCLUDES = -I/usr/include -Imlx
else
		INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_DIR		=	./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname), Linux)
		MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
		MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif


LIBFT_DIR	=	libft/
LIBFT   	=	$(LIBFT_DIR)libft.a
# LINK_FLAGS	=	-L$(LIBFT_DIR) -lft

SRCS     	=	src/test_mlx.c			\

				# src/main.c				\
				# src/init_game.c			\
				# src/input_validation.c	\
				# src/read_file.c			\
				# src/parse_file.c		\
				# src/free.c				\
				# src/general_utils.c		\
				# src/parsing_utils.c     \

OBJS     	=	$(SRCS:%.c=%.o) 

RM			=	rm -rf

all:		$(MLX_LIB) $(LIBFT) $(NAME)

.c.o:
			$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(LIBFT):
			@make -C $(LIBFT_DIR)

$(MLX_LIB):
			@make -C $(MLX_DIR)

clean:
			$(RM) $(OBJS)
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(LIBFT_DIR) fclean

re: 		fclean all

.PHONY: 	all clean fclean re
