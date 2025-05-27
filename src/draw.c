/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:10:51 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/27 18:25:19 by oohnivch         ###   ########.fr       */
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
		bruh(data, "Error\nRay wall not found\n", 1);
	put_floor(data, i, end_y);
	put_fat_pixel(data, WIDTH / 2, HEIGHT / 2, 0xFFCC00CC);
	free(ray);
}

void	draw_frame(t_data *data)
{
	float	fraction;
	float	start_x;
	int		i;

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
	long	check;
	check = get_time(data) - data->time->last_frame;
	printf("\t\t\t\t\t\t\t\t\tframe time: %ld ms\n", check);
	if (check < FRAME_TIME)
		return (0);
	data->time->last_frame = get_time(data);
	draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
