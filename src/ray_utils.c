/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:12:59 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/01 14:54:58 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance(t_data *data, float ray_x, float ray_y)
{
	float	angle;
	float	dist;
	float	x;
	float	y;

	x = ray_x - data->player->x;
	y = ray_y - data->player->y;
	angle = atan2f(y, x) - data->player->dir;
	if (angle < -PI)
		angle += 2 * PI;
	else if (angle > PI)
		angle -= 2 * PI;
	dist = sqrtf(((x * x) + (y * y))) * cosf(angle);
	return (dist);
}

bool	coll(t_data *data, float pos_x, float pos_y)
{
	int	x;
	int	y;

	x = (int)(pos_x / VOX);
	y = (int)(pos_y / VOX);
	if (x < 0 || x >= data->map_width
		|| y < 0 || y >= data->map_height)
		return (false);
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}

bool	edge(t_data *data, float pos_x, float pos_y)
{
	(void)data;
	if ((int)pos_x % VOX == 0 || (int)pos_x % VOX == VOX - 1
		|| (int)pos_y % VOX == 0 || (int)pos_y % VOX == VOX - 1)
		return (true);
	return (false);
}
