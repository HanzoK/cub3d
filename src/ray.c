/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:30:02 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/12 13:48:23 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool coll(t_data *data, float pos_x, float pos_y)
{
	int	x;
	int	y;

	x = (int)(pos_x / VOX);
	y = (int)(pos_y / VOX);
	if (x < 0 || x >= data->map_width
		|| y < 0 || y >= data->map_height)
		return (true);
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}

bool edge(t_data *data, float pos_x, float pos_y)
{
	(void)data;
	if ((int)pos_x % VOX == 0 || (int)pos_x % VOX == VOX - 1
		|| (int)pos_y % VOX == 0 || (int)pos_y % VOX == VOX - 1)
		return (true);
	return (false);
}

int	cast_ray1(t_data *data, float start_x, float *ray_x, float *ray_y)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		step_count;

	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);
	*ray_x = data->player->x;
	*ray_y = data->player->y;
	step_count = 0;
	while (!coll(data, *ray_x, *ray_y))
	{
		*ray_x += ray_dir_x;
		*ray_y += ray_dir_y;
		step_count++;
	}
	return (step_count);
}


int	cast_ray2(t_data *data, float start_x, float *ray_x, float *ray_y)
{
	// set ray start pos
	*ray_x = data->player->x;
	*ray_y = data->player->y;

	// current grid pos
	int		map_x;
	int		map_y;
	map_x = (int)(*ray_x / VOX);
	map_y = (int)(*ray_y / VOX);

	// ray direction vector
	float	ray_dir_x;
	float	ray_dir_y;
	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);

	// distance to next grid line
	float	delta_dist_x;
	float	delta_dist_y;
	delta_dist_x = fabs((float)VOX / ray_dir_x);
	delta_dist_y = fabs((float)VOX / ray_dir_y);

	// step direction and distance
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	side_dist_x = 0;
	side_dist_y = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		/*side_dist_x = (*ray_x - map_x * VOX) / VOX * delta_dist_x;*/
	}
	else
	{
		step_x = 1;
		/*side_dist_x = ((map_x + 1) * VOX - *ray_x) / VOX * delta_dist_x;*/
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		/*side_dist_y = (*ray_y - map_y * VOX) / VOX * delta_dist_y;*/
	}
	else
	{
		step_y = 1;
		/*side_dist_y = ((map_y + 1) * VOX - *ray_y) / VOX * delta_dist_y;*/
	}
	/*side_dist_x = powf(side_dist_x, 2) + */
	while (!edge(data, *ray_x + side_dist_x, *ray_y + side_dist_y))
	{
		side_dist_x += ray_dir_x;
		side_dist_y += ray_dir_y;
		map_x += step_x;
		map_y += step_y;
	}

	printf("side_dist_x: %f side_dist_y: %f delta_dist_x: %f delta_dist_y: %f\n",
		side_dist_x, side_dist_y, delta_dist_x, delta_dist_y);
	if (side_dist_x < side_dist_y)
		printf("hit vertical wall\n");
	else
		printf("hit horizontal wall\n");
	// DDA
	int		side;
	int		step_count;
	step_count = 0;
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		step_count++;
		if (data->map[map_y][map_x] == '1')
			break ;
	}

	// find the collision point
	float perp_dist;
	if (side == 0)
		perp_dist = (map_x - *ray_x + (float)(1 - step_x) / 2) / ray_dir_x;
	else
		perp_dist = (map_y - *ray_y + (float)(1 - step_y) / 2) / ray_dir_y;
	*ray_x += ray_dir_x * perp_dist;
	*ray_y += ray_dir_y * perp_dist;
	return (step_count);
}

int	cast_ray3(t_data *data, float start_x, float *ray_x, float *ray_y)
{
	float	init_x;
	float	init_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		step_count = 0;

	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);

	*ray_x = data->player->x;
	*ray_y = data->player->y;
	init_x = *ray_x;
	init_y = *ray_y;

	int	map_x = (int)(*ray_x / VOX);
	int	map_y = (int)(*ray_y / VOX);

	while (1)
	{
		if (data->map[map_y][map_x] == '1')
			break;
		*ray_x += ray_dir_x;
		*ray_y += ray_dir_y;
		step_count++;
	}
	return (step_count);
}

// senior version
/*int	cast_ray2(t_data *data, float start_x, float *ray_x, float *ray_y)*/
/*{*/
/*	*ray_x = data->player->x;*/
/*	*ray_y = data->player->y;*/
/**/
/*	// Ray direction*/
/*	float ray_dir_x = cos(start_x);*/
/*	float ray_dir_y = sin(start_x);*/
/**/
/*	// Player position in pixel space*/
/*	float pos_x = *ray_x;*/
/*	float pos_y = *ray_y;*/
/**/
/*	// Map coordinates*/
/*	int map_x = (int)(pos_x / VOX);*/
/*	int map_y = (int)(pos_y / VOX);*/
/**/
/*	// Length to move to cross one grid*/
/*	float delta_dist_x = fabs(1.0f / ray_dir_x);*/
/*	float delta_dist_y = fabs(1.0f / ray_dir_y);*/
/**/
/*	// Step direction*/
/*	int step_x = ray_dir_x < 0 ? -1 : 1;*/
/*	int step_y = ray_dir_y < 0 ? -1 : 1;*/
/**/
/*	// Distance to first side*/
/*	float side_dist_x = (ray_dir_x < 0)*/
/*		? (pos_x - map_x * VOX) / fabs(ray_dir_x)*/
/*		: ((map_x + 1) * VOX - pos_x) / fabs(ray_dir_x);*/
/**/
/*	float side_dist_y = (ray_dir_y < 0)*/
/*		? (pos_y - map_y * VOX) / fabs(ray_dir_y)*/
/*		: ((map_y + 1) * VOX - pos_y) / fabs(ray_dir_y);*/
/**/
/*	// Scale delta to match pixel size steps*/
/*	delta_dist_x *= VOX;*/
/*	delta_dist_y *= VOX;*/
/*	side_dist_x *= VOX;*/
/*	side_dist_y *= VOX;*/
/**/
/*	int side = 0;*/
/*	int step_count = 0;*/
/**/
/*	while (1)*/
/*	{*/
/*		if (side_dist_x < side_dist_y)*/
/*		{*/
/*			side_dist_x += delta_dist_x;*/
/*			map_x += step_x;*/
/*			side = 0;*/
/*		}*/
/*		else*/
/*		{*/
/*			side_dist_y += delta_dist_y;*/
/*			map_y += step_y;*/
/*			side = 1;*/
/*		}*/
/*		step_count++;*/
/**/
/*		if (map_y < 0 || map_x < 0 || !data->map[map_y] || data->map[map_y][map_x] == '\0')*/
/*			break; // safety check*/
/**/
/*		if (data->map[map_y][map_x] == '1')*/
/*			break;*/
/*	}*/
/**/
/*	// Distance to wall*/
/*	float dist;*/
/*	if (side == 0)*/
/*		dist = (map_x * VOX - pos_x + (step_x < 0 ? VOX : 0)) / ray_dir_x;*/
/*	else*/
/*		dist = (map_y * VOX - pos_y + (step_y < 0 ? VOX : 0)) / ray_dir_y;*/
/**/
/*	// Final hit point in pixels*/
/*	*ray_x = pos_x + ray_dir_x * dist;*/
/*	*ray_y = pos_y + ray_dir_y * dist;*/
/**/
/*	return step_count;*/
/*}*/
