/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/30 13:21:45 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_game_ready(t_data *data)
{
	t_tx	*tx;
	int		map_ok;

	tx = data->file->tx;
	map_ok = validate_map(data);
	if (!tx->north
		|| !tx->south
		|| !tx->west
		|| !tx->east
		|| !tx->floor
		|| !tx->ceiling
		|| !tx->sprite
		|| !map_ok)
		data->is_game_ready = false;
/*	if (!validate_xpm_64(data->mlx, tx->north)
	 	|| !validate_xpm_64(data->mlx, tx->south)
	 	|| !validate_xpm_64(data->mlx, tx->west)
	 	|| !validate_xpm_64(data->mlx, tx->east)
		|| !validate_xpm_64(data->mlx, tx->sprite))
		data->is_game_ready = false;*/
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
	t_tx		tx;
	//int			i;

	ft_set_up_game(&data, &file, &tx);
	input_validation(argc, argv);
	if (!start_up_game(argv, &data))
		bruh(&data, "Error\nInvalid map or missing config values\n", 1);
 	/*printf("NORTH texture: %s\n", tx.north);
	printf("SOUTH texture: %s\n", tx.south);
	printf("WEST texture: %s\n", tx.west);
	printf("EAST texture: %s\n", tx.east);
	printf("SPRITE texture: %s\n\n", tx.sprite);
	printf("Floor colour (R,G,B): %d,%d,%d\n", tx.floor_r, tx.floor_g, tx.floor_b);
	printf("Ceil  colour (R,G,B): %d,%d,%d\n\n", tx.ceiling_r, tx.ceiling_g, tx.ceiling_b);
	printf("Map size: %d rows | %d cols\n\n", data.map_height, data.map_width);
	i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}*/
	/*data.mlx = mlx_init();
	if (!data.mlx)
		bruh (&data, "Error\n mlx_init fail.\n", 1);
	data.win = mlx_new_window(data.mlx, 1024, 1024, "cub3D");
	if (!data.win)
		bruh (&data, "Error\n window cceation fail\n", 1);
	data.img_north = mlx_xpm_file_to_image(data.mlx, data.tx->north, 64, 64);
	data.img_south = mlx_xpm_file_to_image(data.mlx, data.tx->south, 64, 64);
	data.img_west = mlx_xpm_file_to_image(data.mlx, data.tx->west, 64, 64);
	data.img_east = mlx_xpm_file_to_image(data.mlx, data.tx->east, 64, 64);*/
	bruh(&data, NULL, 0);
}
