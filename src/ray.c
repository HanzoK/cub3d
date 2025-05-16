/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:30:02 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/16 15:07:20 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*init_ray(t_data *data, float direction)
{
	t_ray	*ray;

	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return (bruh(data, "Error: malloc failed", 0), NULL);
	ray->x = data->player->x;
	ray->y = data->player->y;
	ray->dir = direction;
	ray->x_dir = cos(direction);
	ray->y_dir = sin(direction);
	ray->x_step_size = VOX * sqrtf(1 + \
			(ray->y_dir / ray->x_dir) * (ray->y_dir / ray->x_dir));
	ray->y_step_size = VOX * sqrtf(1 + \
			(ray->x_dir / ray->y_dir) * (ray->x_dir / ray->y_dir));
	ray->map_x = (int)(ray->x / VOX);
	ray->map_y = (int)(ray->y / VOX);
	ray->step_x = 1 - (2 * (ray->x_dir < 0));
	ray->step_y = 1 - (2 * (ray->y_dir < 0));
	return (ray);
}

void	ray_init_len(t_ray *ray)
{
	if (ray->x_dir < 0)
		ray->x_len = (ray->x - ray->map_x * VOX) * ray->x_step_size / VOX;
	else
		ray->x_len = ((ray->map_x + 1) * VOX - ray->x) * ray->x_step_size / VOX;
	if (ray->y_dir < 0)
		ray->y_len = (ray->y - ray->map_y * VOX) * ray->y_step_size / VOX;
	else
		ray->y_len = ((ray->map_y + 1) * VOX - ray->y) * ray->y_step_size / VOX;
}

void	dda(t_data *data, t_ray *ray)
{
	while (1)
	{
		if (ray->x_len < ray->y_len)
		{
			ray->map_x += ray->step_x;
			ray->x_len += ray->x_step_size;
			ray->wall = 1 + 2 * (ray->step_x > 0);
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->y_len += ray->y_step_size;
			ray->wall = 0 + 2 * (ray->step_y < 0);
		}
		if (ray->map_x >= 0 && ray->map_x < data->map_width
			&& ray->map_y >= 0 && ray->map_y < data->map_height)
		{
			if (data->map[ray->map_y][ray->map_x] == '1')
				break ;
		}
	}
}

void	ray_get_wall_column(t_data *data, t_ray *ray)
{
	float	pos;
	float	check;

	if (ray->wall == NORTH || ray->wall == SOUTH)
	{
		check = ray->map_x * VOX + ((VOX - 1) * ray->wall == NORTH);
		pos = fabs(ray->x - check);
		if (ray->wall == NORTH)
		{
			ray->column = (int)(pos / VOX * (double)data->tx->north->width);
			ray->column = data->tx->north->width - ray->column;
		}
		else
			ray->column = (int)(pos / VOX * (double)data->tx->north->width);
	}
	else
	{
		check = ray->map_y * VOX + ((VOX - 1) * ray->wall == EAST);
		pos = fabs(ray->y - check);
		if (ray->wall == EAST)
		{
			ray->column = (int)(pos / VOX * (double)data->tx->east->width);
			ray->column = data->tx->east->width - ray->column;
		}
		else
			ray->column = (int)(pos / VOX * (double)data->tx->west->width);
	}
	ray->column *= 4;
}

t_ray	*cast_ray(t_data *data, float direction)
{
	t_ray	*ray;

	ray = init_ray(data, direction);
	ray_init_len(ray);
	dda(data, ray);
	if (ray->wall % 2)
	{
		ray->x = ray->x + ray->x_dir * (ray->x_len - ray->x_step_size);
		ray->y = ray->y + ray->y_dir * (ray->x_len - ray->x_step_size);
	}
	else
	{
		ray->x = ray->x + ray->x_dir * (ray->y_len - ray->y_step_size);
		ray->y = ray->y + ray->y_dir * (ray->y_len - ray->y_step_size);
	}
	ray_get_wall_column(data, ray);
	return (ray);
}

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
	// ADD WALL HERE
	// AFTER SMOKE
	return (0);
}

