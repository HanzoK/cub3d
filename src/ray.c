/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:30:02 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 10:31:32 by oohnivch         ###   ########.fr       */
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
		if (ray->map_x >= 0 && ray->map_x < data->map_w
			&& ray->map_y >= 0 && ray->map_y < data->map_h)
		{
			if (data->map[ray->map_y][ray->map_x] == '1')
				break ;
		}
	}
}

// This function calculates the column index for 
// the wall texture based on the ray's position and direction.
// It determines which wall texture to use 
// (north, south, east, or west) and calculates the column index
// based on the ray's intersection point with the wall.
// "p" stands for the position of the ray relative to the wall it hit.
void	ray_get_wall_column(t_data *data, t_ray *ray)
{
	float	p;

	if (ray->wall == NORTH || ray->wall == SOUTH)
	{
		p = fabs(ray->x - ray->map_x * VOX + ((VOX - 1) * ray->wall == NORTH));
		if (ray->wall == NORTH)
		{
			ray->column = (int)(p / VOX * (double)data->tx->north->width);
			ray->column = data->tx->north->width - ray->column;
		}
		else
			ray->column = (int)(p / VOX * (double)data->tx->north->width);
	}
	else
	{
		p = fabs(ray->y - ray->map_y * VOX + ((VOX - 1) * ray->wall == EAST));
		if (ray->wall == EAST)
		{
			ray->column = (int)(p / VOX * (double)data->tx->east->width);
			ray->column = data->tx->east->width - ray->column;
		}
		else
			ray->column = (int)(p / VOX * (double)data->tx->west->width);
	}
	ray->column *= 4 * (ray->column >= 0);
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
