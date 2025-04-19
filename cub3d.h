/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:06:21 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:24:24 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}				t_direction;

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
	char			**colour_floor;
	char			**colour_ceiling;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;

}					t_textures;

typedef struct s_fileparse
{
	char			**texture;
	char			**map;
	char			**file;
	char			player_direction;
	int				line_length;
	int				line_height;
	int				player_pos_x;
	int				player_pos_y;
	int				fd;
	int				i;
	t_textures		*textures;
}					t_fileparse;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			**map;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
	bool			is_game_ready;
	t_fileparse		*file;
}				t_data;

//*****************************************************************
//*					MAP VALIDATION FUNCTIONS					  *
//*****************************************************************

void	ft_set_up_game(t_data *data);
void	input_validation(int argc, char **argv);
bool	validate_map(t_data *data);


//*****************************************************************
//*					MAP READING FUNCTIONS						  *
//*****************************************************************

char	*read_file_into_line(char	*filename);
char	**arrange_lines_as_map(char	*filename);
int		read_file(t_fileparse *file, char *filename);
int		is_space_line(char *line);
char    *extract_config_values(char *line);
int		parse_colour_config(t_textures *tx, char *line, int is_it_floor);
int		parse_config_file(t_fileparse *file);
char	**fill_map(t_fileparse *file, int map_start);

//*****************************************************************
//*						FREE FUNCTIONS							  *
//*****************************************************************

void	free_lines(char **lines);

//*****************************************************************
//*						FREE FUNCTIONS							  *
//*****************************************************************

char	*join2(char const *s1, char const *s2);

#endif
