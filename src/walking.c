/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:44:52 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 10:35:13 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	wall(t_data *data, float x, float y, float speed)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / VOX);
	map_y = (int)(y / VOX);
	if (map_x < 0 || map_x >= data->map_w
		|| map_y < 0 || map_y >= data->map_h)
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	return (speed);
}

void	walk_forward(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;
	int			x1;
	int			y1;
	int			x2;
	int			y2;

	check = VOX / 4 * (1 - 2 * (x_spd < 0));
	x1 = (int)(pl->x + check);
	x2 = (int)(pl->x + x_spd * 2);
	y1 = (int)(pl->y);
	if (!out_of_bounds(data, x1, y1)
		&& !out_of_bounds(data, x2, y1)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y1 / VOX][x2 / VOX] != '1')
		pl->x += wall(data, pl->x + x_spd * 2, pl->y, x_spd);
	check = VOX / 4 * (1 - 2 * (y_spd < 0));
	x1 = (int)(pl->x);
	y1 = (int)(pl->y + check);
	y2 = (int)(pl->y + y_spd * 2);
	if (!out_of_bounds(data, x1, y1)
		&& !out_of_bounds(data, x1, y2)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y2 / VOX][x1 / VOX] != '1')
		pl->y += wall(data, pl->x, pl->y + y_spd * 2, y_spd);
}

void	walk_backward(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;
	int			x1;
	int			y1;
	int			x2;
	int			y2;

	check = VOX / 4 * (1 - 2 * (x_spd < 0));
	x1 = (int)(pl->x - check);
	x2 = (int)(pl->x - x_spd * 2);
	y1 = (int)(pl->y);
	if (!out_of_bounds(data, x1, y1)
		&& !out_of_bounds(data, x2, y1)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y1 / VOX][x2 / VOX] != '1')
		pl->x -= wall(data, pl->x - x_spd * 2, pl->y, x_spd);
	check = VOX / 4 * (1 - 2 * (y_spd < 0));
	x1 = (int)(pl->x);
	y1 = (int)(pl->y - check);
	y2 = (int)(pl->y - y_spd * 2);
	if (!out_of_bounds(data, x1, y1)
		&& !out_of_bounds(data, x1, y2)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y2 / VOX][x1 / VOX] != '1')
		pl->y -= wall(data, pl->x, pl->y - y_spd * 2, y_spd);
}

void	strafe_left(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;
	int			x1;
	int			y1;
	int			x2;
	int			y2;

	check = VOX / 4 * (1 - 2 * (y_spd < 0));
	y1 = (int)(pl->y);
	x1 = (int)(pl->x + check);
	x2 = (int)(pl->x + y_spd * 2);
	if (!out_of_bounds(data, x1, y1)
		&& !out_of_bounds(data, x2, y1)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y1 / VOX][x2 / VOX] != '1')
		pl->x += wall(data, pl->x + y_spd * 2, pl->y, y_spd);
	check = VOX / 4 * (1 - 2 * (x_spd < 0));
	x1 = (int)(pl->x);
	y1 = (int)(pl->y - check);
	y2 = (int)(pl->y - x_spd * 2);
	if (!out_of_bounds(data, pl->x, y1)
		&& !out_of_bounds(data, pl->x, y2)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y2 / VOX][x1 / VOX] != '1')
		pl->y -= wall(data, pl->x, pl->y - x_spd * 2, x_spd);
}

void	strafe_right(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	int			check;
	int			x1;
	int			y1;
	int			x2;
	int			y2;

	check = VOX / 4 * (1 - 2 * (y_spd < 0));
	y1 = (int)(pl->y);
	x1 = (int)(pl->x - check);
	x2 = (int)(pl->x - y_spd * 2);
	if (!out_of_bounds(data, x1, y1)
		&& !out_of_bounds(data, x2, y1)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y1 / VOX][x2 / VOX] != '1')
		pl->x -= wall(data, pl->x - y_spd * 2, pl->y, y_spd);
	check = VOX / 4 * (1 - 2 * (x_spd < 0));
	x1 = (int)(pl->x);
	y1 = (int)(pl->y + check);
	y2 = (int)(pl->y + x_spd * 2);
	if (!out_of_bounds(data, pl->x, y1)
		&& !out_of_bounds(data, pl->x, y2)
		&& data->map[y1 / VOX][x1 / VOX] != '1'
		&& data->map[y2 / VOX][x1 / VOX] != '1')
		pl->y += wall(data, pl->x, pl->y + x_spd * 2, x_spd);
}
