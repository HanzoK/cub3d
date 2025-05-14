/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/14 13:59:44 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_and_set_texture(char  **texture, char *line)
{
    if (*texture)
        return (0);
    *texture = get_config_value(line, 2);
    if (!*texture)
        return (0);
    return (1);
}

int parse_colour_config(t_data *data, char *line, int is_it_floor)
{
    char    **colours;
    char    *value;
    t_textures    *tx;

    tx = data->file->tx;
    value = get_config_value(line, 1);
    if (!value)
        return (0);
    colours = ft_split(value, ',');
    if (!colours)
        return (ft_free(&value), 0);
    if (arr_len(colours) != 3)
        return(ft_free(&value), free_array(colours), 0);
    if (!rgb_value_check(colours))
        (ft_free(&value), free_array(colours), bruh (data, "Colours, bruh.\n", 1));
    if (is_it_floor)
    {
        tx->floor = value;
        tx->colour_floor = colours;
        tx->floor_r = ft_atoi(colours[0]);
        tx->floor_g = ft_atoi(colours[1]);
        tx->floor_b = ft_atoi(colours[2]);
    }
    else
    {
        tx->ceiling = value;
        tx->colour_ceiling = colours;
        tx->ceiling_r = ft_atoi(colours[0]);
        tx->ceiling_g = ft_atoi(colours[1]);
        tx->ceiling_b = ft_atoi(colours[2]);
    }
    data->sky = get_color(tx->ceiling_r, tx->ceiling_g, tx->ceiling_b);
    data->floor = get_color(tx->floor_r, tx->floor_g, tx->floor_b);
    return (1);
}

int	parse_config_file(t_data *data)
{
    char	*line;
    int		i;
    char    *trimmed;

    trimmed = NULL;
    i = 0;
    while (data->file->file[i])
    {
        line = data->file->file[i];
        trimmed = line + skip_spaces(line, 0);
        if (!ft_strncmp(trimmed, "NO", 2))
        {
            if (!check_and_set_texture(&data->file->tx->north, line))
                return (-1);
        }
        else if (!ft_strncmp(line, "SO", 2))
        {
            if (!check_and_set_texture(&data->file->tx->south, line))
                return (-1);
        }
        else if (!ft_strncmp(line, "WE", 2))
        {
            if (!check_and_set_texture(&data->file->tx->west, line))
                return (-1);
        }
        else if (!ft_strncmp(line, "EA", 2))
        {
            if (!check_and_set_texture(&data->file->tx->east, line))
                return (-1);
        }
        else if (!ft_strncmp(line, "S", 1))
        {
            if (!check_and_set_texture(&data->file->tx->sprite, line))
                return (-1);
        }
        else if (!ft_strncmp(trimmed, "F", 1))
        {
            if (data->file->tx->floor)
                return (-1);
            if (!parse_colour_config(data, line, 1))
                return (-1);
        }
        else if (!ft_strncmp(trimmed, "C", 1))
        {
            if (data->file->tx->ceiling)
                return (-1);
            if (!parse_colour_config(data, line, 0))
                return (-1);
        }
        else if (is_space_line(line))
            ;
        else
            break;
        i++;
    }
    return (i);
}

char	**fill_map(t_data *data, int map_start)
{
	int		rows;
	int		max_len;
	int		len;
	int		i;

	rows = 0;
    max_len = 0;
    i = 0;
	while (data->file->file[map_start + rows])
		rows++;
	if (rows < 1)
		return (NULL);
	while (i < rows)
	{
		len = ft_strlen(data->file->file[map_start + i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	data->map = ft_calloc(rows + 1, sizeof(char *));
	if (!data->map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(data->file->file[map_start + i]);
		data->map[i] = ft_calloc(max_len + 1, sizeof(char));
		if (!data->map[i])
			return (free_array(data->map), NULL);
		ft_memcpy(data->map[i], data->file->file[map_start + i], len);
		while (len < max_len)
			data->map[i][len++] = ' ';
		i++;
	}
    data->map[rows] = NULL;
	data->map_width = max_len;
	data->map_height = rows;
	return (data->map);
}
