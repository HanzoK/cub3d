/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/13 14:05:46 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_game_ready(t_data *data)
{
	t_tx	*tx;
	int		map_ok;

	tx = data->file->tx;
	map_ok = validate_map(data);
	if (!tx->north
		|| !tx->south
		|| !tx->west
		|| !tx->east
		|| !tx->floor
		|| !tx->ceiling
		|| !tx->sprite
		|| !map_ok)
		data->is_game_ready = false;
/*	if (!validate_xpm_64(data->mlx, tx->north)
	 	|| !validate_xpm_64(data->mlx, tx->south)
	 	|| !validate_xpm_64(data->mlx, tx->west)
	 	|| !validate_xpm_64(data->mlx, tx->east)
		|| !validate_xpm_64(data->mlx, tx->sprite))
		data->is_game_ready = false;*/
	else
		data->is_game_ready = true;
}

int start_up_game(char **argv, t_data *data)
{
	int map_start;

	if (!read_file(data, argv[1]))
		return (0);
	map_start = parse_config_file(data);
	if (map_start < 0)
		return (0);
	if (!fill_map(data, map_start))
		return (0);
	check_game_ready(data);
	if (!data->is_game_ready)
		return (0);
	return (1);
}

int key_hook(int keycode, t_data *data)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == ESC)
		bruh(data, "Exit game", 0);
	/*if (keycode == ESC)*/
	/*{*/
	/*	mlx_destroy_window(data->mlx, data->win);*/
	/*	data->win = NULL;*/
	/*}*/
	if (keycode == R)
		color_screen(data, 0xFFFF0000);
	if (keycode == G)
		color_screen(data, 0xFF00FF00);
	if (keycode == B)
		color_screen(data, 0xFF0000FF);
	if (keycode == E)
		evening(data);
	if (keycode == M)
		morning(data);
	put_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
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

float	distance(t_data *data, float ray_x, float ray_y)
{
	float	angle;
	float 	dist;
	float	x;
	float	y;

	x = ray_x - data->player->x;
	y = ray_y - data->player->y;
	angle = atan2f(y, x) - data->player->dir;
	dist = sqrtf(powf(x, 2) + powf(y, 2)) * cosf(angle);
	return (dist);
}

int	shade_color(float dist, int color)
{
	int	alpha;
	int	red;
	int	green;
	int	blue;

	alpha = (color >> 24) & 0xFF;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;

	float ratio = dist / DRAW_DIST;
	red = (int)((float)red * (1 - ratio));
	green = (int)((float)green * (1 - ratio));
	blue = (int)((float)blue * (1 - ratio));
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	if (red <= 0)
		red = 1;
	if (green <= 0)
		green = 1;
	if (blue <= 0)
		blue = 1;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	draw_line(t_data *data, float start_x, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end_y;
	int		y;
	float	hit_x;
	float	hit_y;

	/*step_count = cast_ray1(data, start_x , &ray_x, &ray_y);*/
	/*if (data->d == 3)*/
	/*else*/
	/*	if ((int)start_x == (int)data->player->dir)*/
	/*		step_count = cast_ray2(data, start_x , &ray_x, &ray_y);*/
	/*	else*/
	/*		step_count = cast_ray1(data, start_x , &ray_x, &ray_y);*/
	/*if (data->d == 3)*/
	/*	dist = sqrtf(powf(ray_x - data->player->x, 2) + powf(ray_y - data->player->y, 2));*/
	/*else*/
	/*	dist = distance(data, ray_x, ray_y);*/
	/*height = ((float)VOX / dist) * ((float)HEIGHT / 2);*/
	float temp = ray(data, start_x, &hit_x, &hit_y);
	float temp2 = distance(data, hit_x, hit_y);
	if (data->d < 2)
		dist = temp2;
	else if (data->d == 2)
		dist = temp;
	else
		dist = (temp2 + temp) / 2;
	height = ((float)VOX / dist) * ((float)HEIGHT / 2);
	start_y = (HEIGHT - height) / 2;
	end_y = start_y + height;
	y = 0;
	if (data->d != 3)
	{
		while (y < start_y)
		{
			put_pixel(data, i, y, data->sky);
			y++;
		}
	}
	while (start_y < end_y)
	{
		if (data->d == 3)
		{
			if ((i == WIDTH / 2 || i == WIDTH / 2 + 1 || i == WIDTH / 2 - 1) && 
				(start_y == HEIGHT / 2 || start_y == HEIGHT / 2 + 1 ||
				start_y == HEIGHT / 2 - 1))
				put_pixel(data, i, start_y, 0xFF00AAAA);
			else
				put_pixel(data, i, start_y, 0xFFCC0033);
			if (i == WIDTH / 2)
				printf("Distance: %f Hit_X: %f Hit_Y: %f\n", dist, hit_x, hit_y);
		}
		else
		{
			if ((i == WIDTH / 2 || i == WIDTH / 2 + 1 || i == WIDTH / 2 - 1) && 
				(start_y == HEIGHT / 2 || start_y == HEIGHT / 2 + 1 ||
				start_y == HEIGHT / 2 - 1))
				put_pixel(data, i, start_y, 0xFF00AAAA);
			else
				put_pixel(data, i, start_y, shade_color(dist, 0xFFFF0055));
			if (i == WIDTH / 2)
				printf("Distance: %f Hit_X: %f Hit_Y: %f\n", dist, hit_x, hit_y);
			/*if (i == WIDTH / 2)*/
			/*	printf("Distance: %f Steps: %d X: %f Y: %f\n", dist, step_count, data->player->x, data->player->y);*/
		}
		start_y++;
	}
	if (data->d != 3)
	{
		y = end_y;
		while (y < HEIGHT)
		{
			put_pixel(data, i, y, data->floor);
			y++;
		}
	}
}

float	ray(t_data *data, float direction, float *hit_x, float *hit_y)
{
	float	ray_x;
	float	ray_y;
	float	x_dir;
	float	y_dir;
	float	x_step_size;
	float	y_step_size;
	float	x_len;
	float	y_len;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;

	ray_x = data->player->x;
	ray_y = data->player->y;
	x_dir = cos(direction);
	y_dir = sin(direction);
	x_step_size = VOX * sqrtf(1 + (y_dir / x_dir) * (y_dir / x_dir));
	y_step_size = VOX * sqrtf(1 + (x_dir / y_dir) * (x_dir / y_dir));
	map_x = (int)(ray_x / VOX);
	map_y = (int)(ray_y / VOX);
	if (x_dir < 0)
	{
		step_x = -1;
		x_len = (ray_x - map_x * VOX) * x_step_size / VOX;
	}
	else
	{
		step_x = 1;
		x_len = ((map_x + 1) * VOX - ray_x) * x_step_size / VOX;
	}
	if (y_dir < 0)
	{
		step_y = -1;
		y_len = (ray_y - map_y * VOX) * y_step_size / VOX;
	}
	else
	{
		step_y = 1;
		y_len = ((map_y + 1) * VOX - ray_y) * y_step_size / VOX;
	}
	/*int	i = 0;*/
	/*printf("x_step_size: %f y_step_size: %f x_len: %f y_len: %f\n",*/
	/*	x_step_size, y_step_size, x_len, y_len);*/
	int	wall = 0;
	while (1)
	{
		/*put_square(data, map_x * VOX + 1, map_y * VOX + 1, VOX - 2, 0xFF222222);*/
		if (x_len < y_len)
		{
			/*put_fat_pixel(data, ray_x + x_dir * x_len, ray_y + y_dir * x_len, 0xFF00FF00);*/
			map_x += step_x;
			x_len += x_step_size;
			wall = 1;
		}
		else
		{
			/*put_fat_pixel(data, ray_x + x_dir * y_len, ray_y + y_dir * y_len, 0xFFFFFF00);*/
			map_y += step_y;
			y_len += y_step_size;
			wall = 2;
		}
		if (map_x >= 0 && map_x < data->map_width
			&& map_y >= 0 && map_y < data->map_height)
		{
			if (data->map[map_y][map_x] == '1')
			{
				/*put_square(data, map_x * VOX, map_y * VOX, VOX, 0xFF5555FF);*/
				break;
			}
		}
	}
	if (wall == 1)
	{
		*hit_x = ray_x + x_dir * (x_len - x_step_size);
		*hit_y = ray_y + y_dir * (x_len - x_step_size);
		return (x_len - x_step_size);
		printf("hit green at x_len: %f x: %f y: %f\n", x_len, ray_x + x_dir * x_len, ray_y + y_dir * x_len);
		/*put_fat_pixel(data, ray_x + x_dir * (x_len - x_step_size), ray_y + y_dir * (x_len - x_step_size), 0xFFFF00FF);*/
	}
	else if (wall == 2)
	{
		*hit_x = ray_x + x_dir * (y_len - y_step_size);
		*hit_y = ray_y + y_dir * (y_len - y_step_size);
		return (y_len - y_step_size);
		printf("hit yellow at y_len: %f x: %f y: %f\n", y_len, ray_x + x_dir * y_len, ray_y + y_dir * y_len);
		/*put_fat_pixel(data, ray_x + x_dir * (y_len - y_step_size), ray_y + y_dir * (y_len - y_step_size), 0xFFFF00FF);*/
	}
	else
	{
		printf("hit nothing at x_len: %f y_len: %f x: %f y: %f\n", x_len, y_len, ray_x + x_dir * x_len, ray_y + y_dir * y_len);
		put_fat_pixel(data, ray_x + x_dir * x_len, ray_y + y_dir * x_len, 0xFFFF0000);
		return (0);
	}
	if (data->map[map_y][map_x] == '1')
	{
		put_square(data, map_x * VOX, map_y * VOX, VOX, 0xFF5555FF);
		printf("map_x : %d map_y: %d\n", map_x, map_y);
	}

	/*if (coll(data, ray_x + x_dir * x_len, ray_y + y_dir * x_len))*/
	/*	printf("hit green at x_len: %f x: %f y: %f\n", x_len, ray_x + x_dir * x_len, ray_y + y_dir * x_len);*/
	/*else if (coll(data, ray_x + x_dir * y_len, ray_y + y_dir * y_len))*/
	/*	printf("hit yellow at y_len: %f x: %f y: %f\n", y_len, ray_x + x_dir * y_len, ray_y + y_dir * y_len);*/
	return (0);
}

void	rays(t_data *data)
{
	float	fraction;
	float	start_x;
	int		i;

	fraction = PI / 3 / WIDTH;
	start_x = data->player->dir - PI / 6;
	/*fraction = PI / 2 / WIDTH;*/
	/*start_x = data->player->dir - PI / 4;*/
	i = 0;
	while (i < WIDTH)
	{
		/*ray(data);*/
		draw_line(data, start_x, i);
		start_x += fraction;
		i++;
	}
	/*ray_new(data);*/
}

int	draw(t_data *data)
{
//		just 2D map and player pos
	data->time->delta = get_delta_time(data);
	move_player(data);
	if (get_time(data) - data->time->last_frame < FRAME_TIME)
		return (0);
	data->time->last_frame = get_time(data);
	/*wipe(data);*/
	put_map(data);
	put_player(data);
	/*float		ray_x;*/
	/*float		ray_y;*/
	rays(data);
	/*ray_new(data);*/
	/*ray(data, &ray_x, &ray_y);*/
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
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

int main(int argc, char **argv)
{
	t_data 		data;
	t_file 		file;
	t_tx		tx;
	t_time		time;
	//int			i;

	ft_set_up_game(&data, &file, &tx, &time);
	input_validation(argc, argv);
	if (!start_up_game(argv, &data))
		bruh(&data, "Error\nInvalid map or missing config values\n", 1);
 	/*printf("NORTH texture: %s\n", tx.north);
	printf("SOUTH texture: %s\n", tx.south);
	printf("WEST texture: %s\n", tx.west);
	printf("EAST texture: %s\n", tx.east);
	printf("SPRITE texture: %s\n\n", tx.sprite);
	printf("Floor colour (R,G,B): %d,%d,%d\n", tx.floor_r, tx.floor_g, tx.floor_b);
	printf("Ceil  colour (R,G,B): %d,%d,%d\n\n", tx.ceiling_r, tx.ceiling_g, tx.ceiling_b);
	printf("Map size: %d rows | %d cols\n\n", data.map_height, data.map_width);
	i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}*/
	/// Ollie got stuff. Hanju can go for a smoke
	data.sky = 0xFF00AAFF;
	data.floor = 0xFF333333;
	write(1, "Hanju finished\n", 15);
	data.mlx = mlx_init();
	if (!data.mlx)
		bruh (&data, "Error\n mlx_init fail\n", 1);
	write(1, "Mlx init\n", 9);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3D");
	if (!data.win)
		bruh (&data, "Error\n window creation fail\n", 1);
	write(1, "Window created\n", 15);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img)
		bruh (&data, "Error\n image creation fail\n", 1);
	write(1, "Image created\n", 14);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
	if (!data.addr)
		bruh (&data, "Error\n image data address fail\n", 1);
	write(1, "Image data address\n", 19);
	data.player = init_player(&data);
	if (!data.player)
		bruh (&data, "Error\n player malloc fail\n", 1);
	write(1, "Player created\n", 16);
	/*data.img_north = mlx_xpm_file_to_image(data.mlx, data.tx->north, 64, 64);*/
	/*data.img_south = mlx_xpm_file_to_image(data.mlx, data.tx->south, 64, 64);*/
	/*data.img_west = mlx_xpm_file_to_image(data.mlx, data.tx->west, 64, 64);*/
	/*data.img_east = mlx_xpm_file_to_image(data.mlx, data.tx->east, 64, 64);*/
	/*put_player(&data);*/
	data.d = 0;
	get_delta_time(&data);
	data.time->last_frame = get_time(&data);
	printarr(data.map);
	mlx_key_hook(data.win, &key_hook, &data);
	mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win, 3, 1L<<1, key_release, &data);
	mlx_hook(data.win, 17, 0, &button_hook, &data);
	mlx_loop_hook(data.mlx, &draw, &data);
	mlx_loop(data.mlx);
	bruh(&data, NULL, 0);
}
