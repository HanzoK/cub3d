/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:27:13 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*read_file_into_line(char	*filename)
{
	int		fd;
	int		exit_code;
	char	*line;
	char	*result;
	char	*temp;
	char	*buffer;

	buffer = NULL;
	temp = NULL;
	line = NULL;
	result = NULL;
	exit_code = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return(perror("Error in open"), NULL);
	result = ft_strdup("");
	if (!result)
		return (close(fd), NULL);
	line = get_next_line_2(fd, &buffer, &exit_code);
	while (line)
	{
		temp = join2(result, line);
		free(result);
		result = temp;
		free(line);
		line = get_next_line_2(fd, &buffer, &exit_code);
	}
	if (exit_code == -1)
		free(result);
	return (close(fd), result);
}

char	**arrange_lines_as_map(char	*filename)
{
	char	*read_file;
	char	**map;

	read_file = read_file_into_line(filename);
	if (!read_file)
		return (NULL);
	map = ft_split(read_file, '\n');
	free(read_file);
	if (!map)
		return (NULL);
	return (map);
}

void	read_map(t_data *data, char *filename)
{
	int		i;
	int		width;

	i = 0;
	width = 0;
	data->map = arrange_lines_as_map(filename);
	if (!data->map)
		exit(1);
	while (data->map[i])
		i++;
	data->height = i;
	i = 0;
	while (data->map[i])
	{
		width = ft_strlen(data->map[i]);
		if (width > data->width)
			data->width = width;
		i++;
	}
}
