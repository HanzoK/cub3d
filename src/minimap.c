/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:44:16 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/02 12:59:12 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	x = (data->player_x - (WIDTH / 2) / VOX) - 5;
	y = (data->player_y - (HEIGHT / 2) / VOX) - 5;
	while (x < (data->player_x + (WIDTH / 2) / VOX) + 5)
	{
		y = (data->player_y - (HEIGHT / 2) / VOX) - 5;
		while (y < (data->player_y + (HEIGHT / 2) / VOX) + 5)
		{
			if (x < 0 || y < 0 || x >= data->map_width || y >= data->map_height)
			{
				put_square(data, x * MVOX + 1000, y * MVOX + 300, MVOX, 0xFF000000);
				y++;
			}
			else if (data->map[y][x] == '1')
				put_square(data, x * MVOX + 1000, y * MVOX + 300, MVOX, 0xFF0000FF);
			else if (data->map[y][x] == '0')
				put_square(data, x * MVOX + 1000, y * MVOX + 300, MVOX, 0xFF00FF00);
			else if (data->map[y][x] == 'P')
				put_player(data);
			y++;
		}
		x++;
	}
}
