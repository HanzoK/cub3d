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

int is_config_line(char *line)
{
    if (!line)
        return (0);
    if (!ft_strncmp(line, "NO", 3) ||
        !ft_strncmp(line, "SO", 3) ||
        !ft_strncmp(line, "WE", 3) ||
        !ft_strncmp(line, "EA", 3) ||
        !ft_strncmp(line, "F", 2) ||
        !ft_strncmp(line, "C", 2))
        return (1);
    return (0);
}

int parse_textures(t_file *file)
{
    int i;

    i = 0;
    while (file->file[i])
    {
        if (is_config_line(file->file[i]))
        {
            if (!ft_strncmp(file->file[i], "NO", 3))
                file->textures->north = ft_strdup(ft_strtrim(file->file[i], "NO"));
            else if (!ft_strncmp(file->file[i], "SO", 3))
                file->textures->south = ft_strdup(ft_strtrim(file->file[i], "SO"));
            else if (!ft_strncmp(file->file[i], "WE", 3))
                file->textures->west = ft_strdup(ft_strtrim(file->file[i], "WE"));
            else if (!ft_strncmp(file->file[i], "EA", 3))
                file->textures->east = ft_strdup(ft_strtrim(file->file[i], "EA"));
            else if (!ft_strncmp(file->file[i], "F", 2))
                file->textures->floor = ft_strdup(ft_strtrim(file->file[i], "F"));
            else if (!ft_strncmp(file->file[i], "C", 2))
                file->textures->ceiling = ft_strdup(ft_strtrim(file->file[i], "C"));
        }
        i++;
    }
    if (!file->text->north || !file->text->so || !file->text->we ||
        !file->text->east || !file->text->floor || !file->text->ceiling)
        return(0);
    return (i)
}

char    **fill_map(t_file *file, int map_start_index)
{
    int     i;
    int     j;
    int     k;
    int     max_len;
    int     len;
    char    **padded_map;

    map_lines = 0;
    i = 0;
    j = 0;
    k = 0;
    lem = 0;
    max_len = 0;
    while (file->file[map_start_index + map_lines])
        map_lines++;
    if (map_lines < 1)
        return (NULL);
    while (i < map_lines)
    {
        len = ft_strlen(file->file[map_start_index + i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    padded_map = ft_calloc(map_lines + 1, sizeof(char *));
    if (!padded_map)
        return (NULL);
    i = 0;
    while (i < map_lines)
    {
        len = ft_strlen(file->file[map_start_index + i]);
        padded_map[i] = ft_calloc(max_len + 1, sizeof(char));
        if (!padded_map[i])
            return (free_lines(padded_map), NULL);
        ft_strcpy(padded_map[i], file->file[map_start_index + i]);
        k = len;
        while (k < max_len)
        {
            padded_map[i][k] = ' ';
            k++;
        }
    }
    file->line_length = max_len;
    file->line_height = map_lines;
    return (padded_map);
}

