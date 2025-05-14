/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:10:51 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/14 14:10:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_data *data, float start_x, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end_y;
	int		y;
	float	hit_x;
	float	hit_y;

	float temp = ray(data, start_x, &hit_x, &hit_y);
	float temp2 = distance(data, hit_x, hit_y);
	if (data->d < 2)
		dist = temp;
	else if (data->d <= 3)
		dist = temp2;
	else
		dist = (temp2 + temp) / 2;
	height = ((float)VOX / dist) * ((float)WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end_y = start_y + height;
	y = 0;
	while (y < start_y)
	{
		put_pixel(data, i, y, shade_color((y / ((float)HEIGHT / 16 * 7) * DRAW_DIST), data->sky));
		y++;
	}
	while (start_y < end_y)
	{
		if ((i == WIDTH / 2 || i == WIDTH / 2 + 1 || i == WIDTH / 2 - 1) && 
			(start_y == HEIGHT / 2 || start_y == HEIGHT / 2 + 1 ||
			start_y == HEIGHT / 2 - 1))
			put_pixel(data, i, start_y, 0xFF00AAAA);
		else
			put_pixel(data, i, start_y, shade_color(dist, 0xFF770022));
		/*if (i == WIDTH / 2)*/
			/*printf("Distance: %f Hit_X: %f Hit_Y: %f\n", dist, hit_x, hit_y);*/
		start_y++;
	}
	y = end_y;
	while (y < HEIGHT)
	{
		put_pixel(data, i, y, shade_color((((float)HEIGHT / 16 * 15 - y) / ((float)HEIGHT / 2) * DRAW_DIST), data->floor));
		y++;
	}
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
	if (get_time(data) - data->time->last_frame < FRAME_TIME)
		return (0);
	if (get_time(data) - data->time->last_frame > FRAME_TIME * 2)
		printf("Machine is struggling\n");
	data->time->last_frame = get_time(data);
	/*put_map(data);*/
	/*put_player(data);*/
	draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
