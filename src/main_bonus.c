/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/09 21:40:11 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_game_ready(t_data *data)
{
	t_textures	*tx;
	int			map_ok;

	tx = data->file->tx;
	map_ok = validate_map(data);
	if (!tx->north_path
		|| !tx->south_path
		|| !tx->west_path
		|| !tx->east_path
		|| !tx->floor
		|| !tx->ceiling
		|| !map_ok)
		data->is_game_ready = false;
	else
		data->is_game_ready = true;
}

int	start_up_game(char **argv, t_data *data)
{
	int	map_start;

	if (!read_file(data, argv[1]))
		return (0);
	map_start = parse_config_file(data);
	if (map_start < 0)
		return (0);
	if (!fill_map(data, map_start))
		return (0);
	check_game_ready(data);
	if (!data->is_game_ready)
		return (0);
	return (1);
}

int	mouse_move(int x, int y, t_data *data)
{
	float		last_x;
	float		last_y;

	if (!data->mouse_enabled)
		return (0);
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	if (x == data->window_center_x && y == data->window_center_y)
		return (0);
	last_x = (float)(x - data->window_center_x);
	if (last_x != 0.0f)
	{
		last_y = MOUSE_SPEED;
		data->player->dir += last_x * last_y;
		if (data->player->dir < 0)
			data->player->dir += 2 * PI;
		else if (data->player->dir > 2 * PI)
			data->player->dir -= 2 * PI;
	}
	mlx_mouse_move(data->mlx, data->win,
		data->window_center_x, data->window_center_y);
	return (0);
}

void	mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		bruh(data, "Error\n mlx_init fail\n", 1);
	write(1, "\rLOADING TEXTURES [0/4]", 23);
	if (!load_textures(data))
		bruh(data, "Error\n texture validation fail\n", 1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
		bruh(data, "Error\n window creation fail\n", 1);
	data->window_center_x = WIDTH / 2;
	data->window_center_y = HEIGHT / 2;
	data->mouse_enabled = true;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		bruh(data, "Error\n image creation fail\n", 1);
	data->addr = mlx_get_data_addr(data->img,
			&data->bpp, &data->size_line, &data->endian);
	if (!data->addr)
		bruh(data, "Error\n image data address fail\n", 1);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win,
		data->window_center_x, data->window_center_y);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_file		file;
	t_textures	tx;
	t_time		time;

	set_up_game(&data, &file, &tx, &time);
	input_validation(argc, argv);
	if (!start_up_game(argv, &data))
		bruh(&data, "Error\nInvalid map or missing config values", 1);
	mlx(&data);
	data.player = init_player(&data);
	if (!data.player)
		bruh (&data, "Error\n player malloc fail\n", 1);
	get_delta_time(&data);
	data.time->last_frame = get_time(&data);
	mlx_hook(data.win, 6, 1L << 6, &mouse_move, &data);
	data.mouse_enabled = true;
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 0, &button_hook, &data);
	mlx_loop_hook(data.mlx, &draw, &data);
	mlx_loop(data.mlx);
	bruh(&data, NULL, 0);
}
