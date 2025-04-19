/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:05:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:06:10 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	input_validation(int argc, char **argv)
{
	char	*dot_position;

	dot_position = NULL;
	dot_position = ft_strrchr(argv[1], '.');
	if (argc == 1 || argc > 2)
	{
		if (!dot_position || ft_strncmp(dot_position, ".cub", 4) != 0)
			ft_putstr_fd("Error\nMust use a .cub file as argument. Duh.\n", 2);
		else
			ft_putstr_fd("Error\nOnly 1 map allowed, dude. Really?\n", 2);
		exit(1);
	}
}

bool	validate_map(t_data *data)
{
	int		i;
	int		j;
	int		pc;
	char	c;

	pc = 0;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			c = data->map[i][j];
			if (c != '0' && c != '1'
				&& c != 'N' && c != 'S'
				&& c != 'E' && c != 'W'
				&& c != ' ')
				return (false);
			if (c == '0')
			{
				if (i == 0
				|| i == data->map_height - 1
				|| j == 0
				|| j == data->map_width - 1)
					return (false);
				if (data->map[i - 1][j] == ' '
				|| data->map[i + 1][j] == ' '
				|| data->map[i][j - 1] == ' '
				|| data->map[i][j + 1] == ' ')
					return (false);
			}
			if (c == 'N'
			|| c == 'S'
			|| c == 'E'
			|| c == 'W')
				pc++;
			j++;
		}
		i++;
	}
	if (pc == 1)
		return (true);
	else
		return (false);
}