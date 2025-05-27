/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:05:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/27 18:20:53 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_validation(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nAre you sure you know what you're doing?\n", 2);
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nDo you know the definition of insanity?\n", 2);
		exit (1);
	}
}

int	is_valid_map_char(char c)
{
	if (c != '0'
		&& c != '1'
		&& c != 'N'
		&& c != 'S'
		&& c != 'E'
		&& c != 'W'
		&& c != ' ')
		return (0);
	return (1);
}

int	check_map_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!is_valid_map_char(data->map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_and_count_tile(t_data *data, int i, int j, int *pc)
{
	char	c;

	c = data->map[i][j];
	if (c == '0')
	{
		if (i == 0 || i == data->map_height - 1
			|| j == 0 || j == data->map_width - 1)
			return (0);
		if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' ' \
			|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
			return (0);
	}
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player_x = j;
		data->player_y = i;
		data->map_dir = c;
		(*pc)++;
	}
	return (1);
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;
	int	pc;

	if (!check_map_chars(data))
		return (0);
	pc = 0;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (!validate_and_count_tile(data, i, j, &pc))
				return (0);
			j++;
		}
		i++;
	}
	if (pc == 0)
		return (0);
	else
		return (1);
}
