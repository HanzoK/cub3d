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
