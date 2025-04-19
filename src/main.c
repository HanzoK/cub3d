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

int main(int argc, char **argv)
{
	t_data 		data;
	t_fileparse file;
	t_textures	tx;
	int			map_start;
	int			i;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&file, sizeof(file));
	ft_bzero(&tx, sizeof(tx));
	data.file = &file;
	file.textures = &tx;
	//ft_set_up_game(&data);
	input_validation(argc, argv);
	if (!read_file(&file, argv[1]))
		exit(1);
	map_start = parse_config_file(&file);
	if (map_start < 0)
		exit (1);
	data.map = fill_map(&file, map_start);
	if (!data.map)
		return (1);
	data.map_width = file.line_length;
	data.map_height = file.line_height;
 	printf("  NORTH texture: %s\n", tx.north);
	printf("  SOUTH texture: %s\n", tx.south);
	printf("   WEST texture: %s\n", tx.west);
	printf("   EAST texture: %s\n\n", tx.east);
	printf("Floor colour (R,G,B): %d,%d,%d\n", tx.floor_r, tx.floor_g, tx.floor_b);
	printf("Ceil  colour (R,G,B): %d,%d,%d\n\n", tx.ceiling_r, tx.ceiling_g, tx.ceiling_b);
	printf("Map size: %d rows × %d cols\n\n", data.map_height, data.map_width);
	i = 0;
	while (data.map[i])
	{
		printf("ROW %2d: %s\n", i, data.map[i]);
		i++;
	}
	free_lines(data.map);
	free_lines(file.file);
	exit((!(argc || argv)) & 0x7FFFFFFF);
}
