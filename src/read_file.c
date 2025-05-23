/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/23 15:36:44 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_file_into_line(t_data *data, char	*filename)
{
	char	*line;
	char	*result;
	char	*temp;
	char	*buffer;

	buffer = NULL;
	data->fd = open(filename, O_RDONLY);
	if (data->fd == -1)
		return (perror("Error in open"), NULL);
	result = ft_strdup("");
	if (!result)
		return (close(data->fd), NULL);
	line = get_next_line_2(data->fd, &buffer, &data->exit_code);
	while (line)
	{
		temp = join2(result, line);
		free(result);
		result = temp;
		free(line);
		line = get_next_line_2(data->fd, &buffer, &data->exit_code);
	}
	if (data->exit_code == -1)
		free(result);
	return (close(data->fd), result);
}

int	read_file(t_data *data, char *filename)
{
	char	*raw_line;
	char	*trimmed;

	raw_line = read_file_into_line(data, filename);
	if (!raw_line)
		return (0);
	trimmed = ft_strtrim(raw_line, " \t\n");
	if (!trimmed || trimmed[0] == '\0')
		return (ft_free(&trimmed), ft_free(&raw_line), 0);
	data->file->file = ft_split(raw_line, '\n');
	ft_free(&trimmed);
	ft_free(&raw_line);
	if (data->file->file)
		return (1);
	else
		return (0);
}
