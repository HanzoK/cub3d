/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:25:53 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_game_ready(t_data *data)
{
	t_tx		*tx;
	bool		map_ok;

	tx = data->file->tx;
	map_ok = validate_map(data);
	if (!tx->north
		&& !tx->south
		&& !tx->west
		&& !tx->east
		&& !tx->floor
		&& !tx->ceiling
		&& !tx->sprite
		&& !map_ok)
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

int main(int argc, char **argv)
{
	t_data 		data;
	t_file 		file;
	t_tx		tx;
	int			map_start;
	int			i;

	ft_set_up_game(&data, &file, &tx);
	input_validation(argc, argv);
	if (!read_file(&data, argv[1]))
		bruh(&data, "bruh.", 1);
	map_start = parse_config_file(&data);
	if (map_start < 0)
		bruh (&data, NULL, 1);
	fill_map(&data, map_start);
	if (!data.map)
		bruh( &data, NULL, 1);
	check_game_ready(&data);
	if (!data.is_game_ready)
		bruh (&data, "Error\nInvalid map or missing config values\n", 1);
 	printf("NORTH texture: %s\n", tx.north);
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
	}
	bruh(&data, NULL, 0);
}
