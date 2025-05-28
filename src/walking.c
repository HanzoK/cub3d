/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:44:52 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/28 09:50:33 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	wall(t_data *data, float x, float y, float speed)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / VOX);
	map_y = (int)(y / VOX);
	if (map_x < 0 || map_x >= data->map_width
		|| map_y < 0 || map_y >= data->map_height)
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	return (speed);
}

void	walk_forward(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;

	check = 15 * (1 - 2 * (x_spd < 0));
	if (data->map[(int)(pl->y / VOX)][(int)(pl->x + check) / VOX] != '1' &&
		data->map[(int)(pl->y / VOX)][(int)(pl->x + x_spd * 2) / VOX] != '1')
		pl->x += wall(data, pl->x + x_spd * 2, pl->y, x_spd);
	check = 15 * (1 - 2 * (y_spd < 0));
	if (data->map[(int)((pl->y + check) / VOX)][(int)(pl->x / (float)VOX)] != '1' &&
		data->map[(int)((pl->y + y_spd * 2) / VOX)][(int)(pl->x / (float)VOX)] != '1')
		pl->y += wall(data, pl->x, pl->y + y_spd * 2, y_spd);
}

void	walk_backward(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;

	check = 15 * (1 - 2 * (x_spd < 0));
	if (data->map[(int)(pl->y / VOX)][(int)(pl->x - check) / VOX] != '1' &&
		data->map[(int)(pl->y / VOX)][(int)(pl->x - x_spd * 2) / VOX] != '1')
		pl->x -= wall(data, pl->x - x_spd * 2, pl->y, x_spd);
	check = 15 * (1 - 2 * (y_spd < 0));
	if (data->map[(int)((pl->y - check) / VOX)][(int)(pl->x / (float)VOX)] != '1' &&
		data->map[(int)((pl->y - y_spd * 2) / VOX)][(int)(pl->x / (float)VOX)] != '1')
		pl->y -= wall(data, pl->x, pl->y - y_spd * 2, y_spd);
}

void	strafe_left(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;

	check = 15 * (1 - 2 * (y_spd < 0));
	if (data->map[(int)(pl->y + check) / VOX][(int)(pl->x / (float)VOX)] != '1' &&
		data->map[(int)(pl->y + y_spd * 2) / VOX][(int)(pl->x / (float)VOX)] != '1')
		pl->x += wall(data, pl->x + y_spd * 2, pl->y, y_spd);
	check = 15 * (1 - 2 * (x_spd < 0));
	if (data->map[(int)(pl->y / VOX)][(int)((pl->x - check) / VOX)] != '1' &&
		data->map[(int)(pl->y / VOX)][(int)((pl->x - x_spd * 2) / VOX)] != '1')
		pl->y -= wall(data, pl->x, pl->y - x_spd * 2, x_spd);
}

void	strafe_right(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;

	check = 15 * (1 - 2 * (y_spd < 0));
	if (data->map[(int)(pl->y - check) / VOX][(int)(pl->x / (float)VOX)] != '1' &&
		data->map[(int)(pl->y - y_spd * 2) / VOX][(int)(pl->x / (float)VOX)] != '1')
		pl->x -= wall(data, pl->x - y_spd * 2, pl->y, y_spd);
	check = 15 * (1 - 2 * (x_spd < 0));
	if (data->map[(int)(pl->y / VOX)][(int)((pl->x + check) / VOX)] != '1' &&
		data->map[(int)(pl->y / VOX)][(int)((pl->x + x_spd * 2) / VOX)] != '1')
		pl->y += wall(data, pl->x, pl->y + x_spd * 2, x_spd);
}
