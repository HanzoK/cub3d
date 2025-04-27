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
	char			*sprite;
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

}					t_tx;

typedef struct s_file
{
	char			**file;
	int				line_length;
	int				line_height;
	t_tx			*tx;
}					t_file;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img_north;
	void			*img_south;
	void			*img_west;
	void			*img_east;
	char			**map;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
	bool			is_game_ready;
	t_tx			*tx;
	t_file			*file;
}				t_data;

//*****************************************************************
//*					FILE VALIDATION FUNCTIONS					  *
//*****************************************************************

void	ft_set_up_game(t_data *data, t_file *file, t_tx *tx);
void	input_validation(int argc, char **argv);
int		validate_map(t_data *data);
bool	validate_xpm_64(void *mlx, char *path);


//*****************************************************************
//*					FILE READING FUNCTIONS						  *
//*****************************************************************

int		is_numeric_value(char *s);
int		arr_len(char **array);
int		skip_spaces(char *line, int i);
int		is_space_line(char *line);
char	*read_file_into_line(char	*filename);
char	**arrange_lines_as_map(char	*filename);
int		read_file(t_data *data, char *filename);
int		is_space_line(char *line);
int		rgb_value_check (char **colours);
char	*get_config_value(char *line, int config_name_len);
int		parse_colour_config(t_data *data, char *line, int is_it_floor);
int		parse_config_file(t_data *data);
char	**fill_map(t_data *data, int map_start);

//*****************************************************************
//*						FREE FUNCTIONS							  *
//*****************************************************************

void	bruh(t_data *data, char *s, int status);
void	free_array(char **lines);
void	free_textures(t_data *date);

//*****************************************************************
//*						UTIL FUNCTIONS							  *
//*****************************************************************

char	*join2(char const *s1, char const *s2);

#endif
