/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:06:30 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/14 19:44:01 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_fat_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	w;
	int	n;
	int	s;
	int e;

	if (x <= 0 || x >= WIDTH - 1|| y <= 0 || y >= HEIGHT - 1)
		return ;
	i = (y * data->size_line) + (x * (data->bpp / 8));
	w = (y * data->size_line) + ((-1 + x) * (data->bpp / 8));
	e = (y * data->size_line) + ((1 + x) * (data->bpp / 8));
	n = ((-1 + y) * data->size_line) + (x * (data->bpp / 8));
	s = ((1 + y) * data->size_line) + (x * (data->bpp / 8));
	data->addr[i] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
	data->addr[w] = color & 0xFF;
	data->addr[w + 1] = (color >> 8) & 0xFF;
	data->addr[w + 2] = (color >> 16) & 0xFF;
	data->addr[e] = color & 0xFF;
	data->addr[e + 1] = (color >> 8) & 0xFF;
	data->addr[e + 2] = (color >> 16) & 0xFF;
	data->addr[n] = color & 0xFF;
	data->addr[n + 1] = (color >> 8) & 0xFF;
	data->addr[n + 2] = (color >> 16) & 0xFF;
	data->addr[s] = color & 0xFF;
	data->addr[s + 1] = (color >> 8) & 0xFF;
	data->addr[s + 2] = (color >> 16) & 0xFF;
}

/*void	put_pixel_sky(t_data *data, int x, int y, int color)*/
/*{*/
/*	int	red;*/
/*	int	green;*/
/*	int	blue;*/
/**/
/*	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)*/
/*		return ;*/
/*	red = (color >> 16) & 0xFF;*/
/*	green = (color >> 8) & 0xFF;*/
/*	blue = color & 0xFF;*/
/*	float ratio = y / ((float)HEIGHT / 2);*/
/*	red = (int)((float)red * (1 - ratio));*/
/*	green = (int)((float)green * (1 - ratio));*/
/*	blue = (int)((float)blue * (1 - ratio));*/
/*	if (red > 255)*/
/*		red = 255;*/
/*	if (green > 255)*/
/*		green = 255;*/
/*	if (blue > 255)*/
/*		blue = 255;*/
/*	if (red <= 0)*/
/*		red = 1;*/
/*	if (green <= 0)*/
/*		green = 1;*/
/*	if (blue <= 0)*/
/*		blue = 1;*/
/*	color = (255 << 24 | (red << 16) | (green << 8) | blue);*/
	/*i = (y * data->size_line) + (x * (data->bpp / 8));*/
	/*data->addr[i] = color & 0xFF;*/
	/*data->addr[i + 1] = color & 0xFF;*/
	/*data->addr[i + 2] = color & 0xFF;*/
/*}*/
/**/
/*void	put_pixel_floor(t_data *data, int x, int y, int color)*/
/*{*/
/*	int	red;*/
/*	int	green;*/
/*	int	blue;*/
/**/
/*	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)*/
/*		return ;*/
/*	red = (color >> 16) & 0xFF;*/
/*	green = (color >> 8) & 0xFF;*/
/*	blue = color & 0xFF;*/
/*	float ratio = (HEIGHT - y) / ((float)HEIGHT / 2);*/
/*	red = (int)((float)red * (1 - ratio));*/
/*	green = (int)((float)green * (1 - ratio));*/
/*	blue = (int)((float)blue * (1 - ratio));*/
/*	if (red > 255)*/
/*		red = 255;*/
/*	if (green > 255)*/
/*		green = 255;*/
/*	if (blue > 255)*/
/*		blue = 255;*/
/*	if (red <= 0)*/
/*		red = 1;*/
/*	if (green <= 0)*/
/*		green = 1;*/
/*	if (blue <= 0)*/
/*		blue = 1;*/
/*	int	i;*/
/*	i = (y * data->size_line) + (x * (data->bpp / 8));*/
/*	data->addr[i] = color & 0xFF;*/
/*	data->addr[i + 1] = (color >> 8) & 0xFF;*/
/*	data->addr[i + 2] = (color >> 16) & 0xFF;*/
/*}*/
/**/
void	put_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	*lol;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	i = (y * data->size_line) + (x * (data->bpp / 8));
	lol = (int *)&data->addr[i];
	*lol = color;
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
	int	h;

	h = 3;
	y = 0 - h;
	while (y < h)
	{
		x = (0 - h) + (y == (0 - h) || y == h - 1);
		while (x < h - (y == (0 - h) || y == h - 1))
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
			else if (data->map[y][x] != '1' && data->map[y][x] != ' ')
				put_empty_square(data, x * VOX, y * VOX, VOX);
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

void	put_empty_square(t_data *data, int pos_x, int pos_y, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
				put_pixel(data, pos_x + x, pos_y + y, 0xFF333333);
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
