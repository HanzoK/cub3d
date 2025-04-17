/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:25:53 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int main(int argc, char **argv)
{
	t_data 		*data;
	t_file 		*file;

	ft_set_up_game(&data);
	input_validation(argc, argv);
	read_map(&data, argv[1]);
	
	printf("Map dimensions: %d rows,  %d columns\n", data.width, data.height);
	int i = 0;
	while (data.map[i])
	{
		printf("Row %d: %s\n", i, data.map[i]);
		i++;
	}
	/*while (1)*/
	/*{*/
	/*	// magic happens here*/
	/*}*/
	free_lines(data.map);
	exit((!(argc || argv)) & 0x7FFFFFFF);
}
