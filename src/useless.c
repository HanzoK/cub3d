/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:08:43 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/28 09:52:37 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


void	cheat_up(t_player *pl, float x_spd, float y_spd)
{
	pl->x -= x_spd * 0.5;
	pl->y -= y_spd * 0.5;
}

void	cheat_down(t_player *pl, float x_spd, float y_spd)
{
	pl->x += x_spd * 0.5;
	pl->y += y_spd * 0.5;
}

void	cheat_left(t_player *pl, float x_spd, float y_spd)
{
	pl->x -= y_spd * 0.5;
	pl->y += x_spd * 0.5;
}

void	cheat_right(t_player *pl, float x_spd, float y_spd)
{
	pl->x += y_spd * 0.5;
	pl->y -= x_spd * 0.5;
}

void	cheat(t_data *data, t_player *pl, float x_spd, float y_spd)
{
	while (data->map[(int)(pl->y / VOX)][(int)(pl->x / VOX)] == '1')
	{
		if (pl->key_up)
			cheat_up(pl, x_spd, y_spd);
		else if (pl->key_down)
			cheat_down(pl, x_spd, y_spd);
		else if (pl->key_left)
			cheat_left(pl, x_spd, y_spd);
		else if (pl->key_right)
			cheat_right(pl, x_spd, y_spd);
		else
			break ;
	}
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

// void	color_screen(t_data *data, int color)
// {
// 	int x;
// 	int y;
//
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			put_pixel(data, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }
//
// void	evening(t_data *data)
// {
// 	int x;
// 	int y;
//
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH && y < HEIGHT / 2)
// 		{
// 			put_pixel(data, x, y, 0xFFFF9955);
// 			x++;
// 		}
// 		while (x < WIDTH && y >= HEIGHT / 2)
// 		{
// 			put_pixel(data, x, y, 0xFF002200);
// 			x++;
// 		}
// 		y++;
// 	}
// }
//
// void	morning(t_data *data)
// {
// 	int x;
// 	int y;
//
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH && y < HEIGHT / 2)
// 		{
// 			put_pixel(data, x, y, 0xFF66AAFF);
// 			x++;
// 		}
// 		while (x < WIDTH && y >= HEIGHT / 2)
// 		{
// 			put_pixel(data, x, y, 0xFF005511);
// 			x++;
// 		}
// 		y++;
// 	}
// }
//
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

// void	wipe(t_data *data)
// {
// 	int	x;
// 	int	y;
//
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			put_pixel(data, x, y, 0x00000000);
// 			x++;
// 		}
// 		y++;
// 	}
// }
//
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
//
// float	ray_x(t_data *data, int map_x, int map_y, int step_x)
// {
// 	float	dist;
//
// 	if (data->player->x_dir < 0)
// 		dist = (data->player->x - map_x * VOX);
// 	else if (data->player->x_dir > 0)
// 		dist = ((map_x + 1) * VOX - data->player->x);
// 	else
// 		return (WIDTH);
// 	while (1)
// 	{
// 		if (map_x < 0 || map_x >= data->map_width
// 			|| map_y < 0 || map_y >= data->map_height)
// 			break ;
// 		if (data->map[map_y][map_x + step_x] == '1')
// 			break ;
// 		dist += VOX;
// 		map_x += step_x;
// 	}
// 	return (dist);
// }
//
// float	ray_y(t_data *data, int map_x, int map_y, int step_y)
// {
// 	float	dist;
//
// 	if (data->player->y_dir < 0)
// 		dist = (data->player->y - map_y * VOX);
// 	else if (data->player->y_dir > 0)
// 		dist = ((map_y + 1) * VOX - data->player->y);
// 	else
// 		return (HEIGHT);
// 	while (1)
// 	{
// 		if (map_x < 0 || map_x >= data->map_width
// 			|| map_y < 0 || map_y >= data->map_height)
// 			break ;
// 		if (data->map[map_y + step_y][map_x] == '1')
// 			break ;
// 		dist += VOX;
// 		map_y += step_y;
// 	}
// 	return (dist);
// }
//
// void	update_player_distance(t_data *data, t_player *pl)
// {
// 	int	map_x;
// 	int	map_y;
// 	int	step_x;
// 	int	step_y;
//
// 	map_x = (int)(pl->x / VOX);
// 	map_y = (int)(pl->y / VOX);
// 	step_x = 1 - (2 * (pl->x_dir < 0));
// 	step_y = 1 - (2 * (pl->y_dir < 0));
// 	data->player->x_dir = cos(pl->dir);
// 	data->player->y_dir = sin(pl->dir);
// 	pl->x_dist = ray_x(data, map_x, map_y, step_x);
// 	pl->y_dist = ray_y(data, map_x, map_y, step_y);
// }
//
// bool	can_move(t_player *player)
// {
// 	float	x_dist;
// 	float	y_dist;
//
// 	x_dist = player->x_dist;
// 	y_dist = player->y_dist;
// 	if ((!x_dist || x_dist > 20) && 
// 		(!y_dist || y_dist > 20))
// 		return (true);
// 	return (false);
// }
//
void	split_texture(t_texture *tx)
{
	char **split_texture;

	split_texture = ft_calloc(sizeof(char *), tx->height + 1);
	int	y = 0;
	while (y < tx->height)
	{
		split_texture[y] = tx->addr + (y * tx->size_line);
		y++;
	}
	tx->split_texture = split_texture;
}

int	get_pixel(t_texture *tx, int x, int y)
{
	return (*(unsigned int *)&tx->split_texture[y][x * 4]);
}
/*int key_hook(int keycode, t_data *data)*/
/*{*/
/*	printf("Keycode: %d\n", keycode);*/
/*	if (keycode == ESC)*/
/*		bruh(data, "Exit game", 0);*/
	/*if (keycode == ESC)*/
	/*{*/
	/*	mlx_destroy_window(data->mlx, data->win);*/
	/*	data->win = NULL;*/
	/*}*/
/*	if (keycode == R)*/
/*		color_screen(data, 0xFFFF0000);*/
/*	if (keycode == G)*/
/*		color_screen(data, 0xFF00FF00);*/
/*	if (keycode == B)*/
/*		color_screen(data, 0xFF0000FF);*/
/*	if (keycode == E)*/
/*		evening(data);*/
/*	if (keycode == M)*/
/*		morning(data);*/
/*	put_player(data);*/
/*	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);*/
/*	return (0);*/
/*}*/
// flashcasting version
/*int	draw(t_data *data)*/
/*{*/
/*//		just 2D map and player pos*/
/*	data->time->delta = get_delta_time(data);*/
/*	move_player(data);*/
/*	if (get_time(data) - data->time->last_frame < FRAME_TIME)*/
/*		return (0);*/
/*	data->time->last_frame = get_time(data);*/
/*	if (data->d == 0)*/
/*	{*/
/*		wipe(data);*/
/*		put_map(data);*/
/*		put_player(data);*/
/*	}*/
/*	else if (data->d == 1)*/
/*	{*/
/*//		basic 2D raycasting version*/
/*		float		ray_x;*/
/*		float		ray_y;*/
/*		float 	cos_ray;*/
/*		float 	sin_ray;*/
/**/
/*		wipe(data);*/
/*		put_map(data);*/
/*		put_player(data);*/
/*		ray_x = data->player->x;*/
/*		ray_y = data->player->y;*/
/*		cos_ray = cos(data->player->dir);*/
/*		sin_ray = sin(data->player->dir);*/
/*		while (!coll(data, ray_x, ray_y))*/
/*		{*/
/*			put_pixel(data, ray_x, ray_y, 0xFFAA0000);*/
/*			ray_x += cos_ray;*/
/*			ray_y += sin_ray;*/
/*		}*/
/*	}*/
/*//		basic 2D raycasting version with FOV*/
/*	else if (data->d == 2)*/
/*	{*/
/*		float	fraction;*/
/*		float	start_x;*/
/*		int		i;*/
/**/
/*		wipe(data);*/
/*		put_map(data);*/
/*		put_player(data);*/
/*		fraction = PI / 3 / WIDTH;*/
/*		start_x = data->player->dir - PI / 6;*/
/*		i = 0;*/
/*		while (i < WIDTH)*/
/*		{*/
/*			put_ray(data, start_x);*/
/*			start_x += fraction;*/
/*			i++;*/
/*		}*/
/*	}*/
/*//		basic 3D raycasting version*/
/*	else if (data->d >= 3)*/
/*	{*/
/*		float	fraction;*/
/*		float	start_x;*/
/*		int		i;*/
/**/
/*		if (data->d == 3)*/
/*			wipe(data);*/
/*		fraction = PI / 3 / WIDTH;*/
/*		start_x = data->player->dir - PI / 6;*/
/*		i = 0;*/
/*		while (i < WIDTH)*/
/*		{*/
/*			draw_line(data, start_x, i);*/
/*			start_x += fraction;*/
/*			i++;*/
/*		}*/
/*	}*/
/*	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);*/
/*	return (0);*/
/*}*/
int	cast_ray1(t_data *data, float start_x, float *ray_x, float *ray_y)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		step_count;

	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);
	*ray_x = data->player->x;
	*ray_y = data->player->y;
	step_count = 0;
	while (!coll(data, *ray_x, *ray_y))
	{
		*ray_x += ray_dir_x;
		*ray_y += ray_dir_y;
		step_count++;
	}
	return (step_count);
}

int	cast_ray2(t_data *data, float start_x, float *ray_x, float *ray_y)
{
	// set ray start pos
	*ray_x = data->player->x;
	*ray_y = data->player->y;

	// current grid pos
	int		map_x;
	int		map_y;
	map_x = (int)(*ray_x / VOX);
	map_y = (int)(*ray_y / VOX);

	// ray direction vector
	float	ray_dir_x;
	float	ray_dir_y;
	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);

	// distance to next grid line
	float	delta_dist_x;
	float	delta_dist_y;
	delta_dist_x = fabs((float)VOX / ray_dir_x);
	delta_dist_y = fabs((float)VOX / ray_dir_y);

	// step direction and distance
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	side_dist_x = 0;
	side_dist_y = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (*ray_x - map_x * VOX) / VOX * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1) * VOX - *ray_x) / VOX * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (*ray_y - map_y * VOX) / VOX * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1) * VOX - *ray_y) / VOX * delta_dist_y;
	}
	/*side_dist_x = powf(side_dist_x, 2) + */
	while (!edge(data, *ray_x + side_dist_x, *ray_y + side_dist_y))
	{
		side_dist_x += ray_dir_x;
		side_dist_y += ray_dir_y;
		map_x += step_x;
		map_y += step_y;
	}

	printf("side_dist_x: %f side_dist_y: %f delta_dist_x: %f delta_dist_y: %f\n",
		side_dist_x, side_dist_y, delta_dist_x, delta_dist_y);
	if (side_dist_x < side_dist_y)
		printf("hit vertical wall\n");
	else
		printf("hit horizontal wall\n");
	// DDA
	int		side;
	int		step_count;
	step_count = 0;
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		step_count++;
		if (data->map[map_y][map_x] == '1')
			break ;
	}

	// find the collision point
	float perp_dist;
	if (side == 0)
		perp_dist = (map_x - *ray_x + (float)(1 - step_x) / 2) / ray_dir_x;
	else
		perp_dist = (map_y - *ray_y + (float)(1 - step_y) / 2) / ray_dir_y;
	*ray_x += ray_dir_x * perp_dist;
	*ray_y += ray_dir_y * perp_dist;
	return (step_count);
}

int	cast_ray3(t_data *data, float start_x, float *ray_x, float *ray_y)
{
	float	init_x;
	float	init_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		step_count = 0;

	ray_dir_x = cos(start_x);
	ray_dir_y = sin(start_x);

	*ray_x = data->player->x;
	*ray_y = data->player->y;
	init_x = *ray_x;
	init_y = *ray_y;

	int	map_x = (int)(*ray_x / VOX);
	int	map_y = (int)(*ray_y / VOX);

	while (1)
	{
		if (data->map[map_y][map_x] == '1')
			break;
		*ray_x += ray_dir_x;
		*ray_y += ray_dir_y;
		step_count++;
	}
	return (step_count);
}

// senior version
/*int	cast_ray2(t_data *data, float start_x, float *ray_x, float *ray_y)*/
/*{*/
/*	*ray_x = data->player->x;*/
/*	*ray_y = data->player->y;*/
/**/
/*	// Ray direction*/
/*	float ray_dir_x = cos(start_x);*/
/*	float ray_dir_y = sin(start_x);*/
/**/
/*	// Player position in pixel space*/
/*	float pos_x = *ray_x;*/
/*	float pos_y = *ray_y;*/
/**/
/*	// Map coordinates*/
/*	int map_x = (int)(pos_x / VOX);*/
/*	int map_y = (int)(pos_y / VOX);*/
/**/
/*	// Length to move to cross one grid*/
/*	float delta_dist_x = fabs(1.0f / ray_dir_x);*/
/*	float delta_dist_y = fabs(1.0f / ray_dir_y);*/
/**/
/*	// Step direction*/
/*	int step_x = ray_dir_x < 0 ? -1 : 1;*/
/*	int step_y = ray_dir_y < 0 ? -1 : 1;*/
/**/
/*	// Distance to first side*/
/*	float side_dist_x = (ray_dir_x < 0)*/
/*		? (pos_x - map_x * VOX) / fabs(ray_dir_x)*/
/*		: ((map_x + 1) * VOX - pos_x) / fabs(ray_dir_x);*/
/**/
/*	float side_dist_y = (ray_dir_y < 0)*/
/*		? (pos_y - map_y * VOX) / fabs(ray_dir_y)*/
/*		: ((map_y + 1) * VOX - pos_y) / fabs(ray_dir_y);*/
/**/
/*	// Scale delta to match pixel size steps*/
/*	delta_dist_x *= VOX;*/
/*	delta_dist_y *= VOX;*/
/*	side_dist_x *= VOX;*/
/*	side_dist_y *= VOX;*/
/**/
/*	int side = 0;*/
/*	int step_count = 0;*/
/**/
/*	while (1)*/
/*	{*/
/*		if (side_dist_x < side_dist_y)*/
/*		{*/
/*			side_dist_x += delta_dist_x;*/
/*			map_x += step_x;*/
/*			side = 0;*/
/*		}*/
/*		else*/
/*		{*/
/*			side_dist_y += delta_dist_y;*/
/*			map_y += step_y;*/
/*			side = 1;*/
/*		}*/
/*		step_count++;*/
/**/
/*		if (map_y < 0 || map_x < 0 || !data->map[map_y] || data->map[map_y][map_x] == '\0')*/
/*			break; // safety check*/
/**/
/*		if (data->map[map_y][map_x] == '1')*/
/*			break;*/
/*	}*/
/**/
/*	// Distance to wall*/
/*	float dist;*/
/*	if (side == 0)*/
/*		dist = (map_x * VOX - pos_x + (step_x < 0 ? VOX : 0)) / ray_dir_x;*/
/*	else*/
/*		dist = (map_y * VOX - pos_y + (step_y < 0 ? VOX : 0)) / ray_dir_y;*/
/**/
/*	// Final hit point in pixels*/
/*	*ray_x = pos_x + ray_dir_x * dist;*/
/*	*ray_y = pos_y + ray_dir_y * dist;*/
/**/
/*	return step_count;*/
/*}*/
/*int	ray(t_data *data, float *ray_x, float *ray_y)*/
/*{*/
/*	int		step_count;*/
/**/
/*	step_count = 0;*/
/**/
/*	*ray_x = data->player->x;*/
/*	*ray_y = data->player->y;*/
/*	// Ray direction*/
/*	float dir_x = cos(data->player->dir);*/
/*	float dir_y = sin(data->player->dir);*/
/*	// Distance to first side*/
/*	float	len_x;*/
/*	float	len_y;*/
/*	len_x = 0;*/
/*	len_y = 0;*/
/**/
/*	//distance till first grid line*/
/*	len_x = fabs(VOX - (*ray_x - (int)(*ray_x / VOX) * VOX));*/
/*	// Draw to nearest grid line*/
/*	while (!edge(data, *ray_x, *ray_y))*/
/*	{*/
/*		put_pixel(data, *ray_x, *ray_y, 0xFF00AAAA);*/
/*		*ray_x += dir_x;*/
/*		*ray_y += dir_y;*/
/*		step_count++;*/
/*	}*/
/*	float 	step_size_x;*/
/*	float	step_size_y;*/
/*	if (dir_x != 0.0)*/
/*		step_size_x = fabs(VOX / dir_x);*/
/*	else*/
/*		step_size_x = 0;*/
/*	if (dir_y != 0.0)*/
/*		step_size_y = fabs(VOX / dir_y);*/
/*	else*/
/*		step_size_y = 0;*/
/*	if (step_size_x > (float)WIDTH)*/
/*		step_size_x = 0;*/
/*	if (step_size_y > (float)HEIGHT)*/
/*		step_size_y = 0;*/
	/*printf("1dist_x: %f 1dist_y: %f step_dist_x: %f step_dist_y: %f\n",*/
	/*	dist_x, dist_y, step_dist_x, step_dist_y);*/
/*	*ray_x = data->player->x;*/
/*	*ray_y = data->player->y;*/
/*	int map_x = (int)(*ray_x / VOX);*/
/*	int map_y = (int)(*ray_y / VOX);*/
/*	if (dir_x < 0)*/
		/*dist_x = (*ray_x - (int)(map_x * VOX));*/
/*		len_x = (*ray_x - (int)(map_x * step_size_x));*/
/*	else*/
		/*dist_x = ((int)(map_x + 1) * VOX - *ray_x);*/
/*		len_x = ((int)(map_x + 1) * step_size_x - *ray_x);*/
/*	if (dir_y < 0)*/
		/*len_y = (*ray_y - (int)(map_y * VOX));*/
/*		len_y = (*ray_y - (int)(map_y * step_size_y));*/
/*	else*/
		/*len_y = ((int)(map_y + 1) * VOX - *ray_y);*/
/*		len_y = ((int)(map_y + 1) * step_size_y - *ray_y);*/
/*	printf("2dist_x: %f 2dist_y: %f step_dist_x: %f step_dist_y: %f\n",*/
/*		len_x, len_y, step_size_x, step_size_y);*/
/*	float ray_dist_x;*/
/*	float ray_dist_y;*/
/**/
/*	int	step_x = 1 - (2 * (dir_x < 0));*/
/*	int step_y = 1 - (2 * (dir_y < 0));*/
/*	ray_dist_x = len_x * step_size_x / VOX;*/
/*	ray_dist_y = len_y * step_size_y / VOX;*/
/*	printf("ray_dist_x: %f ray_dist_y: %f\n", ray_dist_x, ray_dist_y);*/
	/*printf("dir_x: %lf dir_y: %lf\n", (double)dir_x, (double)dir_y);*/
/*	// Current grid pos*/
	/*// Step direction*/
	/*// FROM HERE ON I NEED DDA*/
	/**/
/*	float	ray_pos_x;*/
/*	float	ray_pos_y;*/
/*	ray_pos_x = *ray_x;*/
/*	ray_pos_y = *ray_y;*/
	/*printf("ray_pos_x: %f ray_pos_y: %f map_x: %d map_y: %d\n",*/
	/*	ray_pos_x, ray_pos_y, map_x, map_y);*/
	/*float new_dist_x;*/
	/*float new_dist_y;*/
/*	int i = 0;*/
/*	float	new_step_x;*/
/*	float	new_step_y;*/
/*	new_step_x = sqrtf(1 + (dir_y / dir_x) * (dir_y / dir_x));*/
/*	new_step_y = sqrtf(1 + (dir_x / dir_y) * (dir_x / dir_y));*/
/*	put_fat_pixel(data, ray_pos_x, ray_pos_y, 0xFF00AAAA);*/
/*	while (!coll(data, ray_pos_x + ray_dist_x * step_x, ray_pos_y + ray_dist_y * step_y))*/
/*	{*/
/*		if ((ray_dist_x != 0 && ray_dist_x < ray_dist_y) || ray_dist_y == 0)*/
/*		{*/
/*			put_fat_pixel(data, ray_pos_x + ray_dist_x * step_x, ray_pos_y, 0xFF00FF00);*/
/*			ray_dist_x += step_size_x;*/
/*			map_x += step_x;*/
			/*ray_pos_x += step_dist_x;*/
			/*ray_pos_y += dir_y * step_dist_x;*/
/*		}*/
/*		else if (ray_dist_x == 0 || ray_dist_x > ray_dist_y)*/
/*		{*/
/*			put_fat_pixel(data, ray_pos_x + ray_dist_x * step_x, ray_pos_y + ray_dist_y * step_y, 0xFFFFFF00);*/
/*			ray_dist_y += step_size_y;*/
/*			map_y += step_y;*/
			/*ray_pos_y += step_dist_y;*/
			/*ray_pos_x += dir_x * step_dist_y;*/
/*		}*/
/*		i++;*/
/*		if (i == 2)*/
/*			break;*/
/*		put_pixel(data, ray_pos_x + ray_dist_x * step_x, ray_pos_y + ray_dist_y * step_y, 0xFFFF00AA);*/
		/*put_fat_pixel(data, ray_pos_x, ray_pos_y, 0xFF00AAAA);*/
/*		step_count++;*/
/*	}*/
/**/
/*	return (step_count);*/
/*}*/
float	distance2(t_data *data, float ray_x, float ray_y, float start_x)
{
	float	angle;
	float 	dist;
	float	x;
	float	y;

	x = ray_x - data->player->x;
	y = ray_y - data->player->y;
	angle = atan2f(y, x) - start_x;
	dist = sqrtf(powf(x, 2) + powf(y, 2)) * cosf(angle);
	return (dist);
}

void	put_ray(t_data *data, float start_x)
{
	float	ray_x;
	float	ray_y;
	float	cos_ray;
	float 	sin_ray;

	cos_ray = cos(start_x);
	sin_ray = sin(start_x);
	ray_x = data->player->x;
	ray_y = data->player->y;
	while (!coll(data, ray_x, ray_y))
	{
		if (edge(data, ray_x, ray_y))
			put_pixel(data, ray_x, ray_y, 0xFF00AAAA);
		else
			put_pixel(data, ray_x, ray_y, 0xFFAA0000);
		ray_x += cos_ray;
		ray_y += sin_ray;
	}
}

