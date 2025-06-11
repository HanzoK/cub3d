/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:12:59 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/09 14:19:48 by oohnivch         ###   ########.fr       */
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

bool	edge(t_data *data, float pos_x, float pos_y)
{
	(void)data;
	if ((int)pos_x % VOX == 0 || (int)pos_x % VOX == VOX - 1
		|| (int)pos_y % VOX == 0 || (int)pos_y % VOX == VOX - 1)
		return (true);
	return (false);
}
