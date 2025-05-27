/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:06:21 by hanjkim           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/23 16:37:20 by oohnivch         ###   ########.fr       */
=======
/*   Updated: 2025/05/27 16:49:36 by oohnivch         ###   ########.fr       */
>>>>>>> han_dev
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
# define FRAME_TIME 1
/*# define IMG_W 128*/
/*# define IMG_H 128*/

typedef enum e_direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	NEAST = 4,
	SEAST = 5,
	SWEST = 6,
	NWEST = 7,
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

typedef struct s_texture
{
	char			*path;
	void			*img;
	char			*addr;
	int				bpp;
	int				width;
	int				height;
	int				size_line;
	int				endian;
	char			**split_texture;
}					t_texture;

typedef struct s_textures
{
	t_texture			*north;
	t_texture			*south;
	t_texture			*west;
	t_texture			*east;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
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

typedef struct s_file
{
	char			**file;
	int				line_length;
	int				line_height;
	t_textures		*tx;
}					t_file;

typedef struct s_player
{
	float			x;
	float			y;
	float			x_dist;
	float			y_dist;
	float			dir;
	float			x_dir;
	float			y_dir;

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

typedef struct s_ray
{
	float		win_x;
	float		x;
	float		y;
	float		dir;
	float		x_dir;
	float		y_dir;
	float		x_step_size;
	float		y_step_size;
	float		x_len;
	float		y_len;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	t_direction wall;
	int			column;
	float		height;
	float		dist;
}				t_ray;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;

	int				wall[4];
	t_time			*time;
	t_player		*player;
	char			**map;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
	int				sky;
	int				floor;
	bool			is_game_ready;
	t_textures		*tx;
	t_file			*file;
	int				d;
	int				fd;
	int				exit_code;
}				t_data;

//*****************************************************************
//*					FILE VALIDATION FUNCTIONS					  *
//*****************************************************************

void	ft_set_up_game(t_data *data, t_file *file, t_textures *tx, t_time *time);
void	input_validation(int argc, char **argv);
int		validate_map(t_data *data);
bool	validate_xpm_64(t_data *data, void *mlx);
int		load_textures(t_data *data);
void	split_texture(t_texture *tx);

//*****************************************************************
//*					FILE READING FUNCTIONS						  *
//*****************************************************************

int		is_numeric_value(char *s);
int		arr_len(char **array);
int		skip_spaces(char *line, int i);
int		is_space_line(char *line);
char	*read_file_into_line(t_data *data, char	*filename);
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
void	draw_frame(t_data *data);
void	draw_line(t_data *data, float start_x, int i);
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
void	put_north_column(t_data *data, t_ray *ray, int y, int end);
void	put_south_column(t_data *data, t_ray *ray, int y, int end);
void	put_west_column(t_data *data, t_ray *ray, int y, int end);
void	put_east_column(t_data *data, t_ray *ray, int y, int end);

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
t_ray 	*cast_ray(t_data *data, float direction);
float	distance(t_data *data, float ray_x, float ray_y);

//*****************************************************************
//*						TIME FUNCTIONS							  *
//*****************************************************************

long	get_time(t_data *data);
long	get_delta_time(t_data *data);

//*****************************************************************
//*						UTIL FUNCTIONS							  *
//*****************************************************************

int		shade_color(float dist, int color);
int		get_color(int red, int green, int blue);
char	*join2(char const *s1, char const *s2);
void	printarr(char **arr);
float	dist(float *start, float *end, float direction);

#endif
