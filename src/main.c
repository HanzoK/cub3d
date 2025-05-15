/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/15 18:52:51 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_game_ready(t_data *data)
{
	t_textures	*tx;
	int		map_ok;

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

int start_up_game(char **argv, t_data *data)
{
	int map_start;

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

int main(int argc, char **argv)
{
	t_data 		data;
	t_file 		file;
	t_textures		tx;
	t_time		time;
	//int			i;

	ft_set_up_game(&data, &file, &tx, &time);
	input_validation(argc, argv);
	if (!start_up_game(argv, &data))
		bruh(&data, "Error\nInvalid map or missing config values\n", 1);
	/// Ollie got stuff. Hanju can go for a smoke
	data.mlx = mlx_init();
	if (!data.mlx)
		bruh (&data, "Error\n mlx_init fail\n", 1);
	write(1, "\rLOADING TEXTURES [0/4]", 23);
	if (!load_textures(&data))
		bruh(&data, "Error\n texture validation fail\n", 1);
	write(1, "Hanju finished\n", 15);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3D");
	if (!data.win)
		bruh (&data, "Error\n window creation fail\n", 1);
	write(1, "Mlx init\n", 9);
	write(1, "Window created\n", 15);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img)
		bruh (&data, "Error\n image creation fail\n", 1);
	write(1, "Image created\n", 14);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
	if (!data.addr)
		bruh (&data, "Error\n image data address fail\n", 1);
	write(1, "Image data address\n", 19);
	data.player = init_player(&data);
	if (!data.player)
		bruh (&data, "Error\n player malloc fail\n", 1);
	write(1, "Player created\n", 16);
	data.d = 0;
	get_delta_time(&data);
	data.time->last_frame = get_time(&data);
	write(1, "Game ready\n", 12);
	printarr(data.map);
	data.floor = 0xFF444444;
	data.sky = 0xFF0077AA;
	mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win, 3, 1L<<1, key_release, &data);
	mlx_hook(data.win, 17, 0, &button_hook, &data);
	mlx_loop_hook(data.mlx, &draw, &data);
	mlx_loop(data.mlx);
	bruh(&data, NULL, 0);
}
