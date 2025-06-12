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
BONUS_NAME	= cub3D_bonus
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
			  raw_map_parsing.c \

BONUS_SRC	= main_bonus.c \
			  color_bonus.c \
			  delta_time.c \
			  draw_bonus.c \
			  free.c \
			  free2.c \
			  general_utils.c \
			  hand_bonus.c \
			  init_game.c \
			  input_validation.c \
			  minimap_bonus.c \
			  parse_file.c \
			  parsing_utils.c \
			  player_bonus.c \
			  put.c \
			  ray.c \
			  ray_utils.c \
			  read_file.c \
			  load_textures.c \
			  fill_map.c \
			  parse_colours.c \
			  walking.c \
			  walls.c \
			  raw_map_parsing.c \
			  player_sprite_bonus.c \
			  player_mouse_bonus.c \

OBJ			= $(SRC:.c=.o)
BONUS_OBJ	= $(BONUS_SRC:.c=.o)
OBJS		= $(addprefix $(OBJDIR), $(OBJ))
BONUS_OBJS	= $(addprefix $(OBJDIR), $(BONUS_OBJ))


all: 		$(OBJDIR) $(NAME) | logo

bonus:		$(OBJDIR) $(BONUS_NAME) | logo_bonus

$(NAME): 	$(LIB) $(OBJS) ./includes/cub3d.h
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm $(LIB) $(MLXFLAGS) #-pg

$(BONUS_NAME): $(LIB) $(BONUS_OBJS) ./includes/cub3d.h
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) -lm $(LIB) $(MLXFLAGS) #-pg

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
	@rm -f $(BONUS_NAME)
	@echo "$(YELLOW)Deleting binaries and $(words $(OBJ)) object file(s) $(NORMAL)" 
	@echo "$(GREEN)Deletion success! $(NORMAL)"

re: fclean all

reb: fclean bonus

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
                                                                           
logo_bonus:
	@echo "$(RED)"
	@echo "	 ░▒▓██████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  "
	@echo "	░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ "
	@echo "	 ░▒▓██████▓▒░   ░▒▓██████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  "
	@echo "$(NORMAL)"

.PHONY: all clean fclean re bonus reb logo logo_bonus
