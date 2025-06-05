/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:06:30 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 08:27:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_column(t_data *data, t_ray *ray, int start_y, int end_y)
{
	if (ray->wall == NORTH)
		put_north_column(data, ray, start_y, end_y);
	else if (ray->wall == SOUTH)
		put_south_column(data, ray, start_y, end_y);
	else if (ray->wall == WEST)
		put_west_column(data, ray, start_y, end_y);
	else if (ray->wall == EAST)
		put_east_column(data, ray, start_y, end_y);
	else
	{
		free(ray);
		return (bruh(data, "Error: put_column failed", 1), 1);
	}
	return (0);
}

void	put_sky(t_data *data, int x, int end)
{
	int	i;
	int	color;

	i = 0;
	while (i <= end)
	{
		color = shade_color((i / ((float)HEIGHT / 16 * 7) \
			* DRAW_DIST), data->sky);
		put_pixel(data, x, i, color);
		i++;
	}
}

void	put_floor(t_data *data, int x, int start)
{
	int	i;
	int	color;

	i = start;
	while (i < HEIGHT)
	{
		color = shade_color((((float)HEIGHT / 16 * 15 - i) \
			/ ((float)HEIGHT / 2) * DRAW_DIST), data->floor);
		put_pixel(data, x, i, color);
		i++;
	}
}

void	put_fat_pixel(t_data *data, int x, int y, int color)
{
	unsigned int	*i;
	unsigned int	*w;
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;

	if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1)
		return ;
	i = (unsigned int *)&data->addr[(y * data->size_line) \
			+ (x * (data->bpp / 8))];
	w = (unsigned int *)&data->addr[(y * data->size_line) \
			+ ((-1 + x) * (data->bpp / 8))];
	e = (unsigned int *)&data->addr[(y * data->size_line) \
			+ ((1 + x) * (data->bpp / 8))];
	n = (unsigned int *)&data->addr[((-1 + y) * data->size_line) \
			+ (x * (data->bpp / 8))];
	s = (unsigned int *)&data->addr[((1 + y) * data->size_line) \
			+ (x * (data->bpp / 8))];
	*i = color;
	*w = color;
	*e = color;
	*n = color;
	*s = color;
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	*lol;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	i = (y * data->size_line) + (x * (data->bpp / 8));
	lol = (int *)&data->addr[i];
	*lol = color;
}
