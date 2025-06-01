/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/01 17:30:54 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_and_init(t_data *data, char *filename, char **out)
{
	data->fd = open(filename, O_RDONLY);
	if (data->fd == -1)
		return (ft_putstr_fd("Error\nFile opening failed\n", 2), 0);
	*out = ft_strdup("");
	if (!*out)
		return (close(data->fd), 0);
	return (1);
}

char	*read_file_into_line(t_data *data, char	*filename)
{
	char	*line;
	char	*result;
	char	*temp;
	char	*buffer;

	buffer = NULL;
	if (!open_and_init(data, filename, &result))
		return (NULL);
	while (1)
	{
		line = get_next_line_2(data->fd, &buffer, &data->exit_code);
		if (data->exit_code == -1)
			return (ft_free(&result), ft_free(&buffer),
				close(data->fd), NULL);
		if (!line)
			break ;
		temp = join2(result, line);
		free(result);
		result = temp;
		free(line);
		if (!result)
			return (ft_free(&buffer), close(data->fd), NULL);
	}
	return (ft_free(&buffer), close(data->fd), result);
}

int	read_file(t_data *data, char *filename)
{
	char	*raw_line;
	char	*trimmed;

	raw_line = read_file_into_line(data, filename);
	if (!raw_line)
		return (0);
	trimmed = ft_strtrim(raw_line, " \t\n");
	if (!trimmed)
		return (ft_free(&raw_line), 0);
	if (trimmed[0] == '\0')
		return (ft_free(&trimmed), ft_free(&raw_line), 0);
	data->file->file = ft_split(raw_line, '\n');
	ft_free(&trimmed);
	ft_free(&raw_line);
	if (data->file->file)
		return (1);
	return (0);
}
