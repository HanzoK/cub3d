/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:10:51 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/16 15:24:43 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*void	put_texture(t_data *data, int x, int y, t_ray *ray)*/
/*{*/
/*	int			tex_x;*/
/*	int			tex_y;*/
/*	int			*color;*/
/*	void		*img;*/
/*	t_texture	*tx;*/
/*	int			i;*/
/**/
/**/
/*	if (ray->wall == NORTH)*/
/*		tx = data->tx->north;*/
/*	else if (ray->wall == SOUTH)*/
/*		tx = data->tx->south;*/
/*	else if (ray->wall == WEST)*/
/*		tx = data->tx->west;*/
/*	else*/
/*		tx = data->tx->east;*/
/*	if (!tx)*/
/*		bruh(data, "Error\ntexture not found\n", 1);*/
/*	int	edge = (HEIGHT - ray->height) / 2 + (ray->height * y >= ((double)HEIGHT / 2));*/
/*	img = tx->img;*/
/*	tex_x = ray->column;*/
/*	tex_y = abs(y - edge) / ray->height * tx->height;*/
/*	i = (tex_y * tx->size_line) + (tex_x * (tx->bpp / 8));*/
/*	if (img)*/
/*		color = (int *)&tx->addr[i];*/
/*	else*/
/*	{*/
/*		color = NULL;*/
/*		bruh(data, "Error\ntexture address failed\n", 1);*/
/*	}*/
		/*color = *(unsigned int *)(img + (tex_y * tx->width + tex_x) * 4);*/
	/*else*/
	/*	*color = 0xFF000000;*/
/*	float dist = ray->dist;*/
/*	put_pixel(data, x, y, (shade_color(dist, *color)));*/
/*}*/
/**/
void	put_north_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	double		tx_y;
	int			color;
	double		increment;
	
	printf("put_north_column\n");
	tx = data->tx->north;
	tx_y = 0;
	increment = ((double)tx->height / (double)ray->height);
	while (y < end)
	{
		printf("y: %d x: %d\n", (int)tx_y, ray->column);
		// color = *(unsigned int *)&tx->split_texture[(int)tx_y][ray->column];
		color = *(unsigned int *)tx->split_texture[(int)tx_y];
		printf("If you see this - its not the split texture\n");
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
	int			edge;
	int			tx_xy[2];
	int			i;
	int			color;

	edge = (HEIGHT - ray->height) / 2;
	tx = data->tx->south;
	tx_xy[0] = ray->column;
	while (y < end)
	{
		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
		i = (tx_xy[1] * tx->size_line) + (tx_xy[0] * (tx->bpp / 8));
		color = *(unsigned int *)&tx->addr[i];
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
	}
}

void	put_west_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	int			edge;
	int			tx_xy[2];
	int			i;
	int			color;

	edge = (HEIGHT - ray->height) / 2;
	tx = data->tx->west;
	tx_xy[0] = ray->column;
	while (y < end)
	{
		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
		i = (tx_xy[1] * tx->size_line) + (tx_xy[0] * (tx->bpp / 8));
		color = *(unsigned int *)&tx->addr[i];
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
	}
}

void	put_east_column(t_data *data, t_ray *ray, int y, int end)
{
	t_texture	*tx;
	int			edge;
	int			tx_xy[2];
	int			i;
	int			color;

	edge = (HEIGHT - ray->height) / 2;
	tx = data->tx->east;
	tx_xy[0] = ray->column;
	while (y < end)
	{
		tx_xy[1] = abs(y - edge) / ray->height * tx->height;
		i = (tx_xy[1] * tx->size_line) + (tx_xy[0] * (tx->bpp / 8));
		color = *(unsigned int *)&tx->addr[i];
		put_pixel(data, ray->win_x, y, shade_color(ray->dist, color));
		y++;
	}
}

void	draw_line(t_data *data, float start_x, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end_y;
	t_ray	*ray;

	ray = cast_ray(data, start_x);
	dist = distance(data, ray->x, ray->y);
	height = ((float)VOX / dist) * ((float)WIDTH / 2);
	ray->height = height;
	ray->dist = dist;
	start_y = (HEIGHT - height) / 2;
	end_y = start_y + height;
	ray->win_x = i;
	put_sky(data, i, start_y);
	if (ray->wall == NORTH)
		put_north_column(data, ray, start_y, end_y);
	else if (ray->wall == SOUTH)
		put_south_column(data, ray, start_y, end_y);
	else if (ray->wall == WEST)
		put_west_column(data, ray, start_y, end_y);
	else if (ray->wall == EAST)
		put_east_column(data, ray, start_y, end_y);
	else
		bruh(data, "Error\nray wall not found\n", 1);
	/*while (start_y < end_y)*/
	/*{*/
	/*	put_texture(data, i, start_y, ray);*/
	/*	start_y++;*/
	/*}*/
	put_floor(data, i, end_y);
	put_fat_pixel(data, WIDTH / 2, HEIGHT / 2, 0xFFCC00CC);
	free(ray);
}

void	draw_frame(t_data *data)
{
	float	fraction;
	float	start_x;
	int		i;

	/*fraction = PI / 2 / WIDTH;*/
	/*start_x = data->player->dir - PI / 4;*/
	fraction = PI / 3 / WIDTH;
	start_x = data->player->dir - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(data, start_x, i);
		start_x += fraction;
		i++;
	}
}

int	draw(t_data *data)
{
	data->time->delta = get_delta_time(data);
	move_player(data);
	if (get_time(data) - data->time->last_frame < FRAME_TIME)
		return (0);
	/*if (get_time(data) - data->time->last_frame > FRAME_TIME * 2)*/
	/*	printf("Machine is struggling\n");*/
	data->time->last_frame = get_time(data);
	/*put_map(data);*/
	/*put_player(data);*/
	draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
