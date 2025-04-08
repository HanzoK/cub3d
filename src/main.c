/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/08 21:16:04 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_up_game(t_data *data)
{
	data->img = NULL;
	data->map = NULL;
	data->width = 0;
	data->height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = NORTH;
}

void	input_validation(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*dot_position;

	line = NULL;
	dot_position = NULL;
	if (argc == 1 || argc > 2)
	{
		if (argc == 1)
			ft_putstr_fd("Error\nMust use a .cub file as argument. Duh.\n", 2);
		else
			ft_putstr_fd("Error\nOnly 1 map allowed, dude. Really?\n", 2);
		exit(1);
	}
	dot_position = ft_strrchr(argv[1], '.');
	if (!dot_position || ft_strncmp(dot_position, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nDo you not know .cub files?\n", 2);
		exit(1);
	}
}

void	read_map(char *filename, t_data *data)
{
	int		fd;
	int		exit_code;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		(perror("Error opening file"), exit(1));
	while (get_next_line_2(fd, &line, &exit_code) > 0)
	{
		if (exit_code == -1)
			(perror("Error while reading map"), free(line), close(fd),
				exit(1));
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S') ||
			ft_strchr(line, 'E') || ft_strchr(line, 'W'))
		{
			data->player_x = ft_atoi(line);
			/*data->player_y = ft_atoi(line + 2);*/
			if (line[0] == 'N')
				data->player_dir = NORTH;
			else if (line[0] == 'S')
				data->player_dir = SOUTH;
			else if (line[0] == 'E')
				data->player_dir = EAST;
			else if (line[0] == 'W')
				data->player_dir = WEST;
		}
		free(line);
	}
	if (ft_strchr(line, '1') || ft_strchr(line, '0'))
		data->map = ft_split(line, '\n');
	(free(line), close(fd));
}

int main(int argc, char **argv)
{
	t_data data;

	ft_set_up_game(&data);
	input_validation(argc, argv);
	read_map(argv[1], &data);
	while (1)
	{
		// magic happens here
	}
	exit((!(argc || argv)) & 0x7FFFFFFF);
}
