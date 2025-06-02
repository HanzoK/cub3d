/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:10:51 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/02 17:34:32 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (put_column(data, ray, start_y, end_y))
	{
		free(ray);
		bruh(data, "Error: put_column failed", 1);
	}
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
	long	check;
	char	*fps;
	char	*tmp;

	data->time->delta = get_delta_time(data);
	move_player(data);
	check = get_time(data) - data->time->last_frame;
	if (check < FRAME_TIME)
		return (0);
	data->time->last_frame = get_time(data);
	draw_frame(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	tmp = ft_itoa(1000 / check);
	fps = join2("FPS: ", tmp);
	free(tmp);
	if (!fps)
		bruh(data, "Error: FPS string allocation failed", 1);
	mlx_string_put(data->mlx, data->win, 10, 20,
		0x000000, fps);
	free(fps);
	return (0);
}
