/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:55 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/05 13:50:15 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] && ft_isspace((unsigned char)line[i]))
		i++;
	return (i);
}

int	arr_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	is_space_line(char *line)
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

int	is_numeric_value(char *s)
{
	int i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*get_config_value(char *line, int config_name_len)
{
	char	*raw_line;
	char	*trimmed_line;
	int		i1;
    int		i2;

    i1 = skip_spaces(line,0);
    i2 = i1 + config_name_len;
	i2 = skip_spaces(line, i2);
	raw_line = line + i2;
	trimmed_line = ft_strtrim(raw_line, " \t\n");
	return (trimmed_line);
}
