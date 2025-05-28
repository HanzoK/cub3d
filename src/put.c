/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:06:30 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/28 10:05:22 by oohnivch         ###   ########.fr       */
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
		return (1);
	return (0);
}

void	put_sky(t_data *data, int x, int end)
{
	int	i;

	i = 0;
	while (i <= end)
	{
		put_pixel(data, x, i, shade_color((i / ((float)HEIGHT / 16 * 7) * DRAW_DIST), data->sky));
		i++;
	}
}

void	put_floor(t_data *data, int x, int start)
{
	int	i;

	i = start;
	while (i < HEIGHT)
	{
		put_pixel(data, x, i, shade_color((((float)HEIGHT / 16 * 15 - i) / ((float)HEIGHT / 2) * DRAW_DIST), data->floor));
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

	if (x <= 0 || x >= WIDTH - 1|| y <= 0 || y >= HEIGHT - 1)
		return ;
	i = (unsigned int *)&data->addr[(y * data->size_line) + (x * (data->bpp / 8))];
	w = (unsigned int *)&data->addr[(y * data->size_line) + ((-1 + x) * (data->bpp / 8))];
	e = (unsigned int *)&data->addr[(y * data->size_line) + ((1 + x) * (data->bpp / 8))];
	n = (unsigned int *)&data->addr[((-1 + y) * data->size_line) + (x * (data->bpp / 8))];
	s = (unsigned int *)&data->addr[((1 + y) * data->size_line) + (x * (data->bpp / 8))];
	*i = color;
	*w = color;
	*e = color;
	*n = color;
	*s = color;
	// data->addr[i] = color & 0xFF;
	// data->addr[i + 1] = (color >> 8) & 0xFF;
	// data->addr[i + 2] = (color >> 16) & 0xFF;
	// data->addr[w] = color & 0xFF;
	// data->addr[w + 1] = (color >> 8) & 0xFF;
	// data->addr[w + 2] = (color >> 16) & 0xFF;
	// data->addr[e] = color & 0xFF;
	// data->addr[e + 1] = (color >> 8) & 0xFF;
	// data->addr[e + 2] = (color >> 16) & 0xFF;
	// data->addr[n] = color & 0xFF;
	// data->addr[n + 1] = (color >> 8) & 0xFF;
	// data->addr[n + 2] = (color >> 16) & 0xFF;
	// data->addr[s] = color & 0xFF;
	// data->addr[s + 1] = (color >> 8) & 0xFF;
	// data->addr[s + 2] = (color >> 16) & 0xFF;
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
