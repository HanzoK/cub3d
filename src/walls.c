/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:29:45 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/27 16:46:17 by oohnivch         ###   ########.fr       */
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

void put_south_column(t_data *data, t_ray *ray, int y, int end)
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
// void	put_north_column(t_data *data, t_ray *ray, int y, int end)
// {
// 	t_texture	*tx;
// 	int			edge;
// 	int			tx_xy[2];
// 	int			i;
// 	int			color;
//
// 	edge = (HEIGHT - ray->height) / 2;
// 	tx = data->tx->north;
// 	tx_xy[0] = ray->column;
// 	while (y < end)
// 	{
// 		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
// 		i = (tx_xy[1] * tx->size_line) + (tx_xy[0]);
// 		color = *(unsigned int *)&tx->addr[i];
// 		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
// 		y++;
// 	}
// }

// void	put_south_column(t_data *data, t_ray *ray, int y, int end)
// {
// 	t_texture	*tx;
// 	int			edge;
// 	int			tx_xy[2];
// 	int			i;
// 	int			color;
//
// 	edge = (HEIGHT - ray->height) / 2;
// 	tx = data->tx->south;
// 	tx_xy[0] = ray->column;
// 	while (y < end)
// 	{
// 		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
// 		i = (tx_xy[1] * tx->size_line) + (tx_xy[0]);
// 		color = *(unsigned int *)&tx->addr[i];
// 		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
// 		y++;
// 	}
// }
//
// void	put_west_column(t_data *data, t_ray *ray, int y, int end)
// {
// 	t_texture	*tx;
// 	int			edge;
// 	int			tx_xy[2];
// 	int			i;
// 	int			color;
//
// 	edge = (HEIGHT - ray->height) / 2;
// 	tx = data->tx->west;
// 	tx_xy[0] = ray->column;
// 	while (y < end)
// 	{
// 		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
// 		i = (tx_xy[1] * tx->size_line) + (tx_xy[0]);
// 		color = *(unsigned int *)&tx->addr[i];
// 		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
// 		y++;
// 	}
// }
//
// void	put_east_column(t_data *data, t_ray *ray, int y, int end)
// {
// 	t_texture	*tx;
// 	int			edge;
// 	int			tx_xy[2];
// 	int			i;
// 	int			color;
//
// 	edge = (HEIGHT - ray->height) / 2;
// 	tx = data->tx->east;
// 	tx_xy[0] = ray->column;
// 	while (y < end)
// 	{
// 		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
// 		i = (tx_xy[1] * tx->size_line) + (tx_xy[0]);
// 		color = *(unsigned int *)&tx->addr[i];
// 		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
// 		y++;
// 	}
// }
