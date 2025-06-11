/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:29:45 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/09 14:14:21 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_north_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	double		tx_y;
	int			color;
	double		increment;

	tx = data->tx->north;
	tx_y = 0;
	increment = ((double)tx->height / (double)ray->height);
	if (y < 0)
	{
		tx_y += (double)-y * increment;
		y = 0;
	}
	while (y < end && y < HEIGHT && (int)tx_y < tx->height)
	{
		color = *(unsigned int *)&tx->split_texture[(int)tx_y][ray->column];
		if (-1 == color)
			color = 0;
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
		tx_y += increment;
		if (tx_y >= tx->height)
			tx_y = 0;
	}
}

void	put_south_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	double		tx_y;
	int			color;
	double		increment;

	tx = data->tx->south;
	tx_y = 0;
	increment = ((double)tx->height / (double)ray->height);
	if (y < 0)
	{
		tx_y += -y * increment;
		y = 0;
	}
	while (y < end && y < HEIGHT)
	{
		color = *(unsigned int *)&tx->split_texture[(int)tx_y][ray->column];
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
		tx_y += increment;
		if (tx_y >= tx->height)
			tx_y = 0;
	}
}

void	put_west_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	double		tx_y;
	int			color;
	double		increment;

	tx = data->tx->west;
	tx_y = 0;
	increment = ((double)tx->height / (double)ray->height);
	if (y < 0)
	{
		tx_y += -y * increment;
		y = 0;
	}
	while (y < end && y < HEIGHT)
	{
		color = *(unsigned int *)&tx->split_texture[(int)tx_y][ray->column];
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
		tx_y += increment;
		if (tx_y >= tx->height)
			tx_y = 0;
	}
}

void	put_east_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	double		tx_y;
	int			color;
	double		increment;

	tx = data->tx->east;
	tx_y = 0;
	increment = ((double)tx->height / (double)ray->height);
	if (y < 0)
	{
		tx_y += -y * increment;
		y = 0;
	}
	while (y < end && y < HEIGHT)
	{
		color = *(unsigned int *)&tx->split_texture[(int)tx_y][ray->column];
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
		tx_y += increment;
		if (tx_y >= tx->height)
			tx_y = 0;
	}
}
