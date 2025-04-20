/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                     :+:      :+:    :+:  */
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

int rgb_value_check (char **colours)
{
    int r;
    int g;
    int b;

    r = ft_atoi(colours[0]);
    g = ft_atoi(colours[1]);
    b = ft_atoi(colours[2]);
    if (!(r >= 0 && r <= 255
        && g >= 0 && g <= 255
        && b >= 0 && b <= 255))
        return (0);
    else
        return (1);
}

char	*get_config_value(char *line, int config_name_len)
{
    char	*value_start;
    char    *trimmed_value;

    value_start = line + config_name_len;
    trimmed_value = ft_strtrim(value_start, " \t\n");
    return (trimmed_value);
}