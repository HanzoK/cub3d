/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:29:31 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/09 20:04:55 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_max_len(t_data *data, int map_start, int rows)
{
	int	i;
	int	len;
	int	max_len;

	i = 0;
	max_len = 0;
	while (i < rows)
	{
		len = ft_strlen(data->file->file[map_start + i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

char	**create_map_array(t_data *data, int map_start, int rows, int max_len)
{
	char	**map;
	int		i;
	int		len;

	map = ft_calloc(rows + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(data->file->file[map_start + i]);
		map[i] = ft_calloc(max_len + 1, sizeof(char));
		if (!map[i])
			return (free_partial_map(map, i), NULL);
		ft_memcpy(map[i], data->file->file[map_start + i], len);
		while (len < max_len)
			map[i][len++] = ' ';
		i++;
	}
	return (map);
}

char	**fill_map(t_data *data, int map_start)
{
	int	rows;
	int	max_len;

	rows = 0;
	while (data->file->file[map_start + rows])
		rows++;
	if (rows < 1)
		return (NULL);
	max_len = get_map_max_len(data, map_start, rows);
	data->map = create_map_array(data, map_start, rows, max_len);
	if (!data->map)
		return (NULL);
	data->map_w = max_len;
	data->map_h = rows;
	return (data->map);
}
