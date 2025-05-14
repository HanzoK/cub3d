/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:10:51 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/14 16:51:22 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_texture(t_data *data, int x, int y, t_ray *ray)
{
	int		tex_x;
	int		tex_y;
	int		color;
	void	*img;


	tex_x = ray->column;
	tex_y = y / ray->height * IMG_H;

	printf("I need a smoke\n");
	if (ray->wall == NORTH)
		img = data->tx->north;
	else if (ray->wall == SOUTH)
		img = data->tx->south;
	else if (ray->wall == WEST)
		img = data->tx->west;
	else
		img = data->tx->east;
	if (img)
		color = *(unsigned int *)(img + (tex_y * IMG_W + tex_x) * 4);
	else
		color = 0xFF000000;
	put_pixel(data, x, y, color);
}

void	draw_line(t_data *data, float start_x, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		y;
	t_ray	*ray;

	ray = cast_ray(data, start_x);
	dist = distance(data, ray->x, ray->y);
	height = ((float)VOX / dist) * ((float)WIDTH / 2);
	ray->height = height;
	start_y = (HEIGHT - height) / 2;
	y = 0;
	while (y < start_y)
	{
		put_pixel(data, i, y, shade_color((y / ((float)HEIGHT / 16 * 7) * DRAW_DIST), data->sky));
		y++;
	}
	y = start_y + height;
	while (start_y < y)
	{
		if ((i == WIDTH / 2 || i == WIDTH / 2 + 1 || i == WIDTH / 2 - 1) && 
			(start_y == HEIGHT / 2 || start_y == HEIGHT / 2 + 1 ||
			start_y == HEIGHT / 2 - 1))
			put_pixel(data, i, start_y, 0xFF00AAAA);
		else
		{
			printf("zsh: segmentation fault (core dumped)\t./cub3D maps/map.cub\n");
			put_texture(data, i, start_y, ray);
			printf("unreachable\n");
		}
			/*put_pixel(data, i, start_y, shade_color(dist, data->wall[ray->wall]));*/
		/*if (i == WIDTH / 2)*/
			/*printf("Distance: %f Hit_X: %f Hit_Y: %f\n", dist, hit_x, hit_y);*/
		start_y++;
	}
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
