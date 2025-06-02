/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:44:16 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/02 15:28:29 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_square(t_data *data, int pos_x, int pos_y,
 int size, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if ((x == 0 || x == size - 1 || y == 0 || y == size - 1) && color != BLACK)
				put_pixel(data, pos_x + x, pos_y + y, 0xFF0000FF);
			else
				put_pixel(data, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	int	map_x;
	int	map_y;
	int	mini_x;
	int	mini_y;

	mini_x = -4;
	mini_y = -4;
	// x = (data->player_x - (WIDTH / 2) / VOX) - 4;
	// y = (data->player_y - (HEIGHT / 2) / VOX) - 4;
	// map_y = data->player_y / VOX - mini_y;
	printf("Player position: (%f, %f)\n", (float)data->player->x, (float)data->player->y);
	while (mini_x <= 4)
	{
		map_x = data->player->x / VOX - mini_x;
		while (mini_y <= 4)
		{
			map_y = data->player->y / VOX - mini_y;
			if (map_x < 0 || map_y < 0 || map_x >= data->map_width || map_y >= data->map_height)
				put_square(data, mini_x * MVOX + 100, mini_y * MVOX + 100, MVOX, 0xFF111111);
			else if (data->map[map_y][map_x] == '1')
				put_square(data, mini_x * MVOX + 100, mini_y * MVOX + 100, MVOX, 0xFF0000FF);
			else if (data->map[map_y][map_x] != '1')
				put_square(data, mini_x * MVOX + 100, mini_y * MVOX + 100, MVOX, 0xFF555555);
			// else if (data->map[y][x] == 'P')
			// 	put_player(data);
			mini_y++;
		}
		mini_y = -4;
		mini_x++;
	}
}
