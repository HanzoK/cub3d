# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 14:07:34 by hanjkim           #+#    #+#              #
#    Updated: 2025/03/31 14:08:54 by hanjkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	=	cub3D

CC			=	cc

CFLAGS  	=	-Wall -Werror -Wextra -g

LIBFT_DIR	=	libft/
PRINTF_DIR	=	ft_printf/

LIBFT   	=	$(LIBFT_DIR)libft.a
PRINTF		=	$(PRINTF_DIR)libftprintf.a

SRC_DIR 	=	src/
SRCS     	=	$(SRC_DIR)/main.c			\

OBJS     	=	$(SRCS:%.c=%.o) 

RM			=	rm -rf

LINK_FLAGS	=	-L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf
MLXFLAGS	=	-lmlx -lXext -lX11 -lm

all:		$(LIBFT) $(PRINTF) $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(PRINTF):
		@make -C $(PRINTF_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(PRINTF)
			$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LINK_FLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			@make -C $(LIBFT_DIR) clean
			@make -C $(PRINTF_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(LIBFT_DIR) fclean
			@make -C $(PRINTF_DIR) fclean

re: 		fclean all

.PHONY: 	all clean fclean re
