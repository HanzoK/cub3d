# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 12:20:51 by oohnivch          #+#    #+#              #
#    Updated: 2025/05/05 15:48:50 by oohnivch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3D
CC			= cc 
CFLAGS		= -Wall -Wextra -Werror -g
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

SRC			= main.c \
			  free.c \
			  general_utils.c \
			  init_game.c \
			  input_validation.c \
			  parse_file.c \
			  parsing_utils.c \
			  read_file.c

OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJDIR), $(OBJ))


all: $(OBJDIR) $(NAME)

$(NAME): 	$(OBJS) $(LIB) | logo
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(LIB)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADER) 

$(OBJDIR):
	@mkdir $(OBJDIR)

$(LIBFT):
	@make --no-print-directory -C $(LIBFTDIR)

$(MLX):
	@make --no-print-directory -C $(MLXDIR)

clean:
	@make --no-print-directory -C $(LIBFTDIR) clean
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)Deleting $(words $(OBJ)) object file(s) $(NORMAL)"
	@echo "$(GREEN)Deletion success! $(NORMAL)"

fclean:
	@make --no-print-directory -C $(LIBFTDIR) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@echo "$(YELLOW)Deleting $(NAME) and $(words $(OBJ)) object file(s) $(NORMAL)" 
	@echo "$(GREEN)Deletion success! $(NORMAL)"

re: fclean all

logo:
	@echo "	 ░▒▓██████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  "
	@echo "	░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	 ░▒▓██████▓▒░   ░▒▓██████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  \n"
                                                                           
                                                                          

.PHONY: all clean fclean re
