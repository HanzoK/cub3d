# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 12:20:51 by oohnivch          #+#    #+#              #
#    Updated: 2025/05/05 13:12:09 by oohnivch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d
CC			= cc 
CFLAGS		= -g
ifeq ($(shell uname), Linux)
	MLXFLAGS  = -lXext -lmlx -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
	# MLX_FLAGS = -I/opt/X11/include -Imlx -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
HEADER		= -I./includes

LIBFTDIR 	= ./libft
LIBFT 		= $(LIBFTDIR)/libft.a
MLXDIR		= ./mlx
MLX			= $(MLXDIR)/libmlx_$(shell uname).a

ifeq ($(shell uname), Linux)
	LIB		= $(LIBFT)
else
	LIB		= $(MLX) $(LIBFT)
endif

SRCDIR		= src/
OBJDIR		= obj/

SRC			= test_mlx.c

OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJDIR), $(OBJ))


all: $(OBJDIR) $(NAME)

$(NAME): 	$(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(LIB)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADER) 

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJDIR)

fclean:
	make -C $(LIBFTDIR) fclean
	# make -C $(MLXDIR) clean
	rm -rf $(OBJDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
