/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:27:13 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_space_line(char *line)
{
    int j;

    j = 0;
    while (line[j] && ft_isspace((unsigned char)line[j]))
        j++;
    if (line[j] == '\0')
        return (1);
    else
        return (0);
}

char    *extract_config_values(char *line)
{
    int     i;
    char    *value;

    i = 0;
    while (line[i] && ft_isspace((unsigned char)line[i]))
        i++;
    while (line[i] && !ft_isspace((unsigned char)line[i]))
        i++;
    while (line[i] && ft_isspace((unsigned char)line[i]))
        i++;
    value = ft_strtrim(line + i, " \t\n");
    return (value);
}

int parse_colour_config(t_textures *tx, char *line, int is_it_floor)
{
    char    **colours;
    char    *value;

    value = extract_config_values(line);
    if (!value)
        return (0);
    colours = ft_split(value, ',');
    if (!colours)
        return (ft_free(&value), 0);
    if (!colours[0] || !colours[1] || !colours[2])
        return(ft_free(&value), free_lines(colours), 0);
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
    return (1);
}

int parse_config_file(t_fileparse *file)
{
    int         i;
    t_textures  *tx;
    char        *line;

    tx = file->textures;
    i = 0;
    line = NULL;
    while (file->file[i])
    {
        line = file->file[i];
        if(is_space_line(line))
        {
            i++;
            continue;
        }
        if (!ft_strncmp(file->file[i], "NO", 2))
            tx->north = extract_config_values(file->file[i]);
        else if (!ft_strncmp(file->file[i], "SO", 2))
            tx->south = extract_config_values(file->file[i]);
        else if (!ft_strncmp(file->file[i], "WE", 2))
            tx->west = extract_config_values(file->file[i]);
        else if (!ft_strncmp(file->file[i], "EA", 2))
            tx->east = extract_config_values(file->file[i]);
        else if (!ft_strncmp(file->file[i], "F", 1))
        {
            if (!parse_colour_config(tx,file->file[i], 1))
                return (-1);
        }
        else if (!ft_strncmp(file->file[i], "C", 1))
        {
            if (!parse_colour_config(tx,file->file[i], 0))
                return (-1);
        }
        else
            break;
        i++;
    }
    if (!tx->north || !tx->south || !tx->west ||
        !tx->east || !tx->floor || !tx->ceiling)
        return(-1);
    return (i);
}

char	**fill_map(t_fileparse *file, int map_start)
{
	char	**map;
	int		rows;
	int		max_len;
	int		len;
	int		i;

	rows = 0;
    max_len = 0;
    i = 0;
	while (file->file[map_start + rows])
		rows++;
	if (rows < 1)
		return (NULL);
	while (i < rows)
	{
		len = ft_strlen(file->file[map_start + i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	map = ft_calloc(rows + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(file->file[map_start + i]);
		map[i] = ft_calloc(max_len + 1, sizeof(char));
		if (!map[i])
			return (free_lines(map), NULL);
		ft_memcpy(map[i], file->file[map_start + i], len);
		while (len < max_len)
			map[i][len++] = ' ';
		i++;
	}
    map[rows] = NULL;
	file->line_length = max_len;
	file->line_height = rows;
	return (map);
}