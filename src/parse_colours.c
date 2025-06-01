/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:40:56 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/01 17:23:30 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	trim_three(char **colours)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < 3)
	{
		tmp = ft_strtrim(colours[i], " \t\n");
		if (!tmp)
			return (free_all_three(colours));
		ft_free(&colours[i]);
		colours[i] = tmp;
		i++;
	}
	return (1);
}

int	check_all_numeric(char **colours)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (!colours[i] || !colours[i][0])
			return (free_all_three(colours));
		j = 0;
		while (colours[i][j])
		{
			if (!ft_isdigit((unsigned char)colours[i][j]))
				return (free_all_three(colours));
			j++;
		}
		i++;
	}
	return (1);
}

int	rgb_value_check(char **colours)
{
	int	r;
	int	g;
	int	b;

	if (!trim_three(colours))
		return (0);
	if (!check_all_numeric(colours))
		return (0);
	r = ft_atoi(colours[0]);
	g = ft_atoi(colours[1]);
	b = ft_atoi(colours[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_all_three(colours), 0);
	return (1);
}

void	assign_colour(t_textures *tx, char *value, char **colours, int is_floor)
{
	if (is_floor)
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
}

int	parse_colour_config(t_data *data, char *line, int is_it_floor)
{
	char		**colours;
	char		*value;
	t_textures	*tx;

	tx = data->file->tx;
	value = get_config_value(line, 1);
	if (!value)
		return (0);
	colours = ft_split(value, ',');
	if (!colours)
		return (ft_free(&value), 0);
	if (arr_len(colours) != 3)
		return (ft_free(&value), free_array(colours), 0);
	if (!rgb_value_check(colours))
		return (ft_free(&value), free_array(colours), 0);
	assign_colour(tx, value, colours, is_it_floor);
	data->sky = get_color(tx->ceiling_r, tx->ceiling_g, tx->ceiling_b);
	data->floor = get_color(tx->floor_r, tx->floor_g, tx->floor_b);
	return (1);
}
