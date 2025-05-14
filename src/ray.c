/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:30:02 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/14 11:59:56 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ray(t_data *data, float direction, float *hit_x, float *hit_y)
{
	float	ray_x;
	float	ray_y;
	float	x_dir;
	float	y_dir;
	float	x_step_size;
	float	y_step_size;
	float	x_len;
	float	y_len;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;


	ray_x = data->player->x;
	ray_y = data->player->y;
	x_dir = cos(direction);
	y_dir = sin(direction);
	x_step_size = VOX * sqrtf(1 + (y_dir / x_dir) * (y_dir / x_dir));
	y_step_size = VOX * sqrtf(1 + (x_dir / y_dir) * (x_dir / y_dir));
	map_x = (int)(ray_x / VOX);
	map_y = (int)(ray_y / VOX);
	if (x_dir < 0)
	{
		step_x = -1;
		x_len = (ray_x - map_x * VOX) * x_step_size / VOX;
	}
	else
	{
		step_x = 1;
		x_len = ((map_x + 1) * VOX - ray_x) * x_step_size / VOX;
	}
	if (y_dir < 0)
	{
		step_y = -1;
		y_len = (ray_y - map_y * VOX) * y_step_size / VOX;
	}
	else
	{
		step_y = 1;
		y_len = ((map_y + 1) * VOX - ray_y) * y_step_size / VOX;
	}
	int	wall = 0;
	while (1)
	{
		/*put_square(data, map_x * VOX + 1, map_y * VOX + 1, VOX - 2, 0xFF222222);*/
		if (x_len < y_len)
		{
			/*put_fat_pixel(data, ray_x + x_dir * x_len, ray_y + y_dir * x_len, 0xFF00FF00);*/
			map_x += step_x;
			x_len += x_step_size;
			wall = 1;
		}
		else
		{
			/*put_fat_pixel(data, ray_x + x_dir * y_len, ray_y + y_dir * y_len, 0xFFFFFF00);*/
			map_y += step_y;
			y_len += y_step_size;
			wall = 2;
		}
		if (map_x >= 0 && map_x < data->map_width
			&& map_y >= 0 && map_y < data->map_height)
		{
			if (data->map[map_y][map_x] == '1')
			{
				/*put_square(data, map_x * VOX, map_y * VOX, VOX, 0xFF5555FF);*/
				break;
			}
		}
	}
	if (wall == 1)
	{
		*hit_x = ray_x + x_dir * (x_len - x_step_size);
		*hit_y = ray_y + y_dir * (x_len - x_step_size);
		return (x_len - x_step_size);
		printf("hit green at x_len: %f x: %f y: %f\n", x_len, ray_x + x_dir * x_len, ray_y + y_dir * x_len);
		/*put_fat_pixel(data, ray_x + x_dir * (x_len - x_step_size), ray_y + y_dir * (x_len - x_step_size), 0xFFFF00FF);*/
	}
	else if (wall == 2)
	{
		*hit_x = ray_x + x_dir * (y_len - y_step_size);
		*hit_y = ray_y + y_dir * (y_len - y_step_size);
		return (y_len - y_step_size);
		printf("hit yellow at y_len: %f x: %f y: %f\n", y_len, ray_x + x_dir * y_len, ray_y + y_dir * y_len);
		/*put_fat_pixel(data, ray_x + x_dir * (y_len - y_step_size), ray_y + y_dir * (y_len - y_step_size), 0xFFFF00FF);*/
	}
	else
	{
		printf("hit nothing at x_len: %f y_len: %f x: %f y: %f\n", x_len, y_len, ray_x + x_dir * x_len, ray_y + y_dir * y_len);
		put_fat_pixel(data, ray_x + x_dir * x_len, ray_y + y_dir * x_len, 0xFFFF0000);
		return (0);
	}
	if (data->map[map_y][map_x] == '1')
	{
		put_square(data, map_x * VOX, map_y * VOX, VOX, 0xFF5555FF);
		printf("map_x : %d map_y: %d\n", map_x, map_y);
	}
	return (0);
}

