/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:06:30 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/06 16:06:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	i;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	i = (y * data->size_line) + (x * (data->bpp / 8));
	data->addr[i] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

void	color_screen(t_data *data, int color)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	evening(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH && y < HEIGHT / 2)
		{
			put_pixel(data, x, y, 0xFFFF9955);
			x++;
		}
		while (x < WIDTH && y >= HEIGHT / 2)
		{
			put_pixel(data, x, y, 0xFF002200);
			x++;
		}
		y++;
	}
}

void	morning(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH && y < HEIGHT / 2)
		{
			put_pixel(data, x, y, 0xFF66AAFF);
			x++;
		}
		while (x < WIDTH && y >= HEIGHT / 2)
		{
			put_pixel(data, x, y, 0xFF005511);
			x++;
		}
		y++;
	}
}

void	put_player(t_data *data)
{
	int	x;
	int	y;

	y = -4;
	while (y < 4)
	{
		x = -4;
		while (x < 4)
		{
			put_pixel(data, data->player->x + x, data->player->y + y, 0xFFFFCCFF);
			x++;
		}
		y++;
	}
}

void	put_map(t_data *data)
{
	int	x;
	int	y;
	int x_lim;
	int y_lim;

	/*printf("PUTTING MAP\n");*/
	x_lim = ft_strlen(data->map[0]);
	y_lim = arr_len(data->map);
	y = 0;
	while (y < y_lim)
	{
		x = 0;
		while (x < x_lim)
		{
			if (data->map[y][x] == '1')
				put_square(data, x * VOX, y * VOX, VOX, 0xFF000088);
			/*else if (data->map[y][x] == '0')*/
			/*	put_square(data, x * VOX, y * VOX, VOX, 0xFF000000);*/
			/*else if (data->map[y][x] == ' ')*/
			/*	put_pixel(data, x, y, 0xFF000000);*/
			x++;
		}
		y++;
	}
}

void	wipe(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(data, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	put_square(t_data *data, int pos_x, int pos_y, int size, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if ((x == 0 || x == size - 1 || y == 0 || y == size - 1) && color != BLACK)
				put_pixel(data, pos_x + x, pos_y + y, 0xFF0000FF);
			else
				put_pixel(data, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}
