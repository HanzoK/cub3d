/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2.15/06/02 12:44:16 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/04 17:21:15 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_mini_ray(t_data *data, float dir, float x, float y)
{
	float 	cos_ray;
	float 	sin_ray;
	int		ray_mysterio;
	int		color;

	cos_ray = cos(dir);
	sin_ray = sin(dir);
	ray_mysterio = 0;
	if (data->player->dash > 1)
		color = D_COLOR;
	else
		color = P_COLOR;
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
	// put_fat_pixel(data, data->player->x, data->player->y, 0xFFFFCCFF);
	if (data->player->dash > 1)
		color = D_COLOR;
	else
		color = P_COLOR;
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

void	draw_minimap(t_data *data)
{
	float	off_x;
	float	off_y;
	int		x;
	int		y;

	off_x = -4 * VOX;
	off_y = -4 * VOX;

	while (off_x <= 4 * VOX)
	{
		x = data->player->x + off_x;
		while (off_y <= 4 * VOX)
		{
			y = data->player->y + off_y;
			if (x < 0 || y < 0 || x >= data->map_width * VOX || y >= data->map_height * VOX)
				put_pixel(data, VOX * 2.15 + off_x / 2, VOX * 2.15 + off_y / 2, 0xFF111111);
			else if (data->map[y / VOX][x / VOX] == '1')
				if (x % VOX == 0 || y % VOX == 0 || (x % VOX == VOX - 1  || y % VOX == VOX - 1))
					put_pixel(data, VOX * 2.15 + off_x / 2, VOX * 2.15 + off_y / 2, 0xFF111111);
				else
					put_pixel(data, VOX * 2.15 + off_x / 2, VOX * 2.15 + off_y / 2, 0xFF553399);
			else
				if (x % VOX == 0 || y % VOX == 0 || (x % VOX == VOX - 1  || y % VOX == VOX - 1))
					put_pixel(data, VOX * 2.15 + off_x / 2, VOX * 2.15 + off_y / 2, 0xFF111111);
				else
					put_pixel(data, VOX * 2.15 + off_x / 2, VOX * 2.15 + off_y / 2, 0xFF222222);
			off_y += 2;
		}
		off_x += 2;
		off_y = -4 * VOX;
	}
	put_player(data, VOX * 2.15, VOX * 2.15);
}

// void	draw_minimap(t_data *data)
// {
// 	int	map_x;
// 	int	map_y;
// 	int	mini_x;
// 	int	mini_y;
//
// 	int	test = 0;
//
// 	mini_x = -4;
// 	mini_y = -4;
// 	// x = (data->player_x - (WIDTH / 2) / VOX) - 4;
// 	// y = (data->player_y - (HEIGHT / 2) / VOX) - 4;
// 	// map_y = data->player_y / VOX - mini_y;
// 	// printf("Player position: (%f, %f)\n", (float)data->player->x, (float)data->player->y);
// 	while (mini_x <= 4)
// 	{
// 		map_x = data->player->x / VOX + mini_x;
// 		while (mini_y <= 4)
// 		{
// 			map_y = data->player->y / VOX + mini_y;
// 			if (map_x < 0 || map_y < 0 || map_x >= data->map_width || map_y >= data->map_height)
// 			{
// 				test++;
// 				put_square(data, mini_x * MVOX + 100, mini_y * MVOX + 100, MVOX, 0xFF111111);
// 				if (test < 10)
// 					printf("Map position: (%d, %d) - Screen position: (%d, %d)\n",
// 						map_x, map_y, mini_x * MVOX + 100, mini_y * MVOX + 100);
// 				// mini_y++;
// 				// continue ;
// 			}
// 			else if (data->map[map_y][map_x] == '1')
// 			{
// 				test++;
// 				put_square(data, mini_x * MVOX + 100, mini_y * MVOX + 100, MVOX, 0xFF0000FF);
// 				if (test < 10)
// 					printf("Map position: (%d, %d) - Screen position: (%d, %d)\n",
// 						map_x, map_y, mini_x * MVOX + 100, mini_y * MVOX + 100);
// 			}
// 			else if (data->map[map_y][map_x] != '1')
// 			{
// 				test++;
// 				put_square(data, mini_x * MVOX + 100, mini_y * MVOX + 100, MVOX, 0xFF555555);
// 				if (test < 10)
// 					printf("Map position: (%d, %d) - Screen position: (%d, %d)\n",
// 						map_x, map_y, mini_x * MVOX + 100, mini_y * MVOX + 100);
// 			// else if (data->map[y][x] == 'P')
// 			// 	put_player(data);
// 			}
// 			mini_y++;
// 		}
// 		mini_y = -4;
// 		mini_x++;
// 	}
// 	put_player_minimap(data);
// }
