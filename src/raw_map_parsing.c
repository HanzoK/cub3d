/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_map_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:32:53 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/10 12:17:30 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_trimmed_line(char *p)
{
	char		*eol;
	size_t		len;
	char		*line;
	char		*trim;

	eol = ft_strchr(p, '\n');
	if (eol)
		len = (size_t)(eol - p);
	else
		len = ft_strlen(p);
	line = ft_strdup(p);
	if (!line)
		return (NULL);
	trim = ft_strtrim(line, " \t\n");
	free(line);
	return (trim);
}

char	*find_map_start(char *raw)
{
	char	*p;
	char	*trim;

	p = raw;
	while (*p)
	{
		trim = get_trimmed_line(p);
		if (!trim)
			return (NULL);
		if (trim[0] != '\0' && ft_strncmp(trim, "NO", 2) != 0
			&& ft_strncmp(trim, "SO", 2) != 0 && ft_strncmp(trim, "WE", 2) != 0
			&& ft_strncmp(trim, "EA", 2) != 0 && ft_strncmp(trim, "F", 1) != 0
			&& ft_strncmp(trim, "C", 1) != 0)
		{
			free(trim);
			break ;
		}
		free(trim);
		if (ft_strchr(p, '\n'))
			p = ft_strchr(p, '\n') + 1;
		else
			p += ft_strlen(p);
	}
	return (p);
}

bool	has_empty_line_after_map(char *raw)
{
	char	*map_row_ptr;
	char	*empty_line_ptr;
	char	*invalid;

	map_row_ptr = find_map_start(raw);
	if (!map_row_ptr)
		return (true);
	while (*map_row_ptr)
	{
		if (*map_row_ptr == '\n')
		{
			empty_line_ptr = map_row_ptr + 1;
			while (*empty_line_ptr == ' ' || *empty_line_ptr == '\t')
				empty_line_ptr++;
			if (*empty_line_ptr == '\n' || *empty_line_ptr == '\0')
			{
				invalid = empty_line_ptr + (*empty_line_ptr == '\n');
				while (*invalid == ' ' || *invalid == '\t' || *invalid == '\n')
					invalid++;
				return (*invalid != '\0');
			}
		}
		map_row_ptr++;
	}
	return (false);
}
