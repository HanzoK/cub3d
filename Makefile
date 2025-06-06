NORMAL 		= \033[0m
RED 		= \033[0;31m
GREEN 		= \033[1;32m
YELLOW 		= \033[0;33m
BLUE 		= \033[0;34m
PURPLE 		= \033[1;35m
CYAN 		= \033[0;36m

# **************************************************************************** #
#                                   Variables                                  #
# **************************************************************************** #
NAME 		= cub3D
CC			= cc 
CFLAGS		= -Wall -Wextra -Werror -g

# MLXFLAGS
ifeq ($(shell uname), Linux)
	MLXFLAGS = -lXext -lmlx -lX11
else
	MLXFLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

# HEADER
ifeq ($(shell uname), Darwin)
	HEADER  = -I/opt/X11/include -Imlx -Iincludes
else
	HEADER  = -I./includes
endif

LIBFTDIR 	= ./libft
LIBFT 		= $(LIBFTDIR)/libft.a
MLXDIR		= ./mlx
MLX			= $(MLXDIR)/libmlx_$(shell uname).a

# LIB
ifeq ($(shell uname), Linux)
	LIB		= $(LIBFT)
else
	LIB		= $(MLX) $(LIBFT)
endif

SRCDIR		= src/
OBJDIR		= obj/
SRC			= main.c \
			  color.c \
			  delta_time.c \
			  draw.c \
			  free.c \
			  free2.c \
			  general_utils.c \
			  init_game.c \
			  input_validation.c \
			  minimap.c \
			  parse_file.c \
			  parsing_utils.c \
			  player.c \
			  put.c \
			  ray.c \
			  ray_utils.c \
			  read_file.c \
			  load_textures.c \
			  fill_map.c \
			  parse_colours.c \
			  walking.c \
			  walls.c \

OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJDIR), $(OBJ))


all: 		$(OBJDIR) $(NAME) | logo

$(NAME): 	$(LIB) $(OBJS) ./includes/cub3d.h
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm $(LIB) $(MLXFLAGS) #-pg

$(OBJDIR)%.o: $(SRCDIR)%.c $(LIB)
	@$(CC) $(CFLAGS) -c -o $@ $< $(HEADER) #-pg

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
	@echo "$(BLUE)"
	@echo "	 ░▒▓██████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  "
	@echo "	░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	 ░▒▓██████▓▒░   ░▒▓██████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  "
	@echo "$(NORMAL)"
                                                                           
.PHONY: all clean fclean re
