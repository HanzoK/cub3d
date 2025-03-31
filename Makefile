# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 14:07:34 by hanjkim           #+#    #+#              #
#    Updated: 2025/03/31 14:17:44 by hanjkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	=	cub3D

CC			=	cc

CFLAGS  	=	-Wall -Werror -Wextra -g

LIBFT_DIR	=	libft/

LIBFT   	=	$(LIBFT_DIR)libft.a

SRC_DIR 	=	src/
SRCS     	=	$(SRC_DIR)/main.c			\

OBJS     	=	$(SRCS:%.c=%.o) 

RM			=	rm -rf

LINK_FLAGS	=	-L$(LIBFT_DIR) -lft -lftprintf
MLXFLAGS	=	-lmlx -lXext -lX11 -lm

all:		$(LIBFT) $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(PRINTF):
		@make -C $(PRINTF_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LINK_FLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(LIBFT_DIR) fclean

re: 		fclean all

.PHONY: 	all clean fclean re
