/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2.15/06/02 12:44:16 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 08:58:47 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_mini_ray(t_data *data, float dir, float x, float y)
{
	float	cos_ray;
	float	sin_ray;
	int		ray_mysterio;
	int		color;

	cos_ray = cos(dir);
	sin_ray = sin(dir);
	ray_mysterio = 0;
	if (data->player->dash > 1)
		color = DASH;
	else
		color = PLAYER;
	while (ray_mysterio < 7)
	{
		if (ray_mysterio < 4)
			put_fat_pixel(data, x + cos_ray, y + sin_ray, color);
		else
			put_pixel(data, x, y, color);
		x += cos_ray;
		y += sin_ray;
		ray_mysterio++;
	}
}

void	put_player(t_data *data, int pl_x, int pl_y)
{
	int	x;
	int	y;
	int	h;
	int	color;

	h = 3;
	y = 0 - h;
	if (data->player->dash > 1)
		color = DASH;
	else
		color = PLAYER;
	while (y < h)
	{
		x = (0 - h) + (y == (0 - h) || y == h - 1);
		while (x < h - (y == (0 - h) || y == h - 1))
		{
			put_pixel(data, pl_x + x, pl_y + y, color);
			x++;
		}
		y++;
	}
	put_mini_ray(data, data->player->dir, pl_x, pl_y);
}

bool	out_of_bounds(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map_w * VOX || y >= data->map_h * VOX)
		return (true);
	return (false);
}

void	draw_minimap(t_data *data, float off_x, float off_y)
{
	int		x;
	int		y;
	double	space;

	space = VOX * 2.15;
	while (off_x <= 4 * VOX)
	{
		x = data->player->x + off_x;
		while (off_y <= 4 * VOX)
		{
			y = data->player->y + off_y;
			if (out_of_bounds(data, x, y))
				put_pixel(data, space + off_x / 2, space + off_y / 2, EDGE);
			else if (edge(data, x, y))
				put_pixel(data, space + off_x / 2, space + off_y / 2, EDGE);
			else if (data->map[y / VOX][x / VOX] == '1')
				put_pixel(data, space + off_x / 2, space + off_y / 2, WALL);
			else
				put_pixel(data, space + off_x / 2, space + off_y / 2, TILE);
			off_y += 2;
		}
		off_x += 2;
		off_y = -4 * VOX;
	}
	put_player(data, VOX * 2.1, VOX * 2.1);
}
