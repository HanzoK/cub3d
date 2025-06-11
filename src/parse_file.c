/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/09 20:01:13 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_and_set_texture(char **texture, char *line)
{
	if (*texture)
		return (0);
	*texture = get_config_value(line, 2);
	if (!*texture)
		return (0);
	return (1);
}

int	handle_texture(t_data *data, char *trimmed, char *line)
{
	if (!ft_strncmp(trimmed, "NO", 2))
	{
		if (!check_and_set_texture(&data->file->tx->north_path, line))
			return (-1);
		return (0);
	}
	if (!ft_strncmp(trimmed, "SO", 2))
	{
		if (!check_and_set_texture(&data->file->tx->south_path, line))
			return (-1);
		return (0);
	}
	if (!ft_strncmp(trimmed, "WE", 2))
	{
		if (!check_and_set_texture(&data->file->tx->west_path, line))
			return (-1);
		return (0);
	}
	if (!ft_strncmp(trimmed, "EA", 2))
	{
		if (!check_and_set_texture(&data->file->tx->east_path, line))
			return (-1);
		return (0);
	}
	return (1);
}

int	handle_colour(t_data *data, char *trimmed, char *line)
{
	if (!ft_strncmp(trimmed, "F", 1))
	{
		if (data->file->tx->floor)
			return (-1);
		if (!parse_colour_config(data, line, 1))
			return (-1);
		return (0);
	}
	if (!ft_strncmp(trimmed, "C", 1))
	{
		if (data->file->tx->ceiling)
			return (-1);
		if (!parse_colour_config(data, line, 0))
			return (-1);
		return (0);
	}
	return (1);
}

int	parse_config_file(t_data *data)
{
	char	*line;
	char	*trimmed;
	int		i;
	int		ret_tex;
	int		ret_col;

	i = 0;
	while (data->file->file[i])
	{
		line = data->file->file[i];
		trimmed = line + skip_spaces(line, 0);
		ret_tex = handle_texture(data, trimmed, line);
		if (ret_tex < 0)
			return (-1);
		if (ret_tex == 0)
			ret_col = 1;
		else
			ret_col = handle_colour(data, trimmed, line);
		if (ret_col < 0)
			return (-1);
		if (ret_tex == 1 && ret_col == 1 && !is_space_line(line))
			break ;
		i++;
	}
	return (i);
}
