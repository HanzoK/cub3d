/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:06:21 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/13 16:11:20 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <mlx.h>
# include <math.h>
# include <sys/time.h>

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265358979323846
# define BLACK 0xFF000000
# define VOX 40
# define SPEED 300
# define TURN_SPEED 3
# define DRAW_DIST 780.0
/*# define FPS 120*/
# define FRAME_TIME 16

typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}				t_direction;

typedef enum e_keycode
{
	ESC = 65307,
	UP = 65362,
	LEFT = 65361,
	DOWN = 65364,
	RIGHT = 65363,
	SHIFT = 65505,
	CTRL = 65507,
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	E = 101,
	Q = 113,
	M = 109,
	P = 112,
	R = 114,
	G = 103,
	B = 98,
	ZERO = 48,
	ONE = 49,
	TWO = 50,
	THREE = 51,
	FOUR = 52,
}				t_keycode;

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

typedef struct s_sprite
{
	void			*north;
	void			*south;
	void			*west;
	void			*east;
}					t_sprite;

typedef struct s_player
{
	float			x;
	float			y;
	float			dir;

	float			dash;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			turn_left;
	bool			turn_right;
}					t_player;

typedef struct s_time
{
	long			last; // last time
	long			last_frame; // last frame time
	long			curr; // current time
	long			delta; // time difference
}					t_time;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;

	t_time			*time;
	t_player		*player;
	t_sprite		*spr;
	char			**map;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
	int				sky;
	int				floor;
	bool			is_game_ready;
	t_tx			*tx;
	t_file			*file;
	int				d;
}				t_data;

//*****************************************************************
//*					FILE VALIDATION FUNCTIONS					  *
//*****************************************************************

void	ft_set_up_game(t_data *data, t_file *file, t_tx *tx, t_time *time);
void	input_validation(int argc, char **argv);
int		validate_map(t_data *data);
bool	validate_xpm_64(void *mlx, char *path);
int		validate_textures(t_data *data);

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
//*						PLAYER FUNCTIONS						  *
//*****************************************************************

t_player	*init_player(t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
void		move_player(t_data *data);
bool 		coll(t_data *data, float pos_x, float pos_y);

//*****************************************************************
//*						DRAW FUNCTIONS							  *
//*****************************************************************

int		draw(t_data *data);
void	wipe(t_data *data);
void	put_map(t_data *data);
void	put_player(t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);
void	put_pixel_sky(t_data *data, int x, int y, int color);
void	put_pixel_floor(t_data *data, int x, int y, int color);
void	put_square(t_data *data, int pos_x, int pos_y, int size, unsigned int color);
void	put_empty_square(t_data *data, int pos_x, int pos_y, int size);
void	put_fat_pixel(t_data *data, int x, int y, int color);
void	color_screen(t_data *data, int color);
void	evening(t_data *data);
void	morning(t_data *data);

//*****************************************************************
//*						FREE FUNCTIONS							  *
//*****************************************************************

void	bruh(t_data *data, char *s, int status);
void	free_array(char **lines);
void	free_textures(t_data *date);
int		button_hook(t_data *data);

//*****************************************************************
//*						RAY FUNCTIONS							  *
//*****************************************************************

bool	edge(t_data *data, float pos_x, float pos_y);
bool	coll(t_data *data, float pos_x, float pos_y);
int		cast_ray1(t_data *data, float start_x, float *ray_x, float *ray_y);
int		cast_ray2(t_data *data, float start_x, float *ray_x, float *ray_y);
float	ray(t_data *data, float direction, float *hit_x, float *hit_y);

//*****************************************************************
//*						TIME FUNCTIONS							  *
//*****************************************************************

long	get_time(t_data *data);
long	get_delta_time(t_data *data);

//*****************************************************************
//*						UTIL FUNCTIONS							  *
//*****************************************************************

int		get_color(int red, int green, int blue);
char	*join2(char const *s1, char const *s2);
void	printarr(char **arr);
float	dist(float *start, float *end, float direction);

#endif
