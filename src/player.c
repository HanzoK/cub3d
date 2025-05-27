/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:16:24 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/27 18:21:48 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_player	*init_player(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = (float)data->player_x * VOX + ((float)VOX / 2);
	player->y = (float)data->player_y * VOX + ((float)VOX / 2);
	if (data->map_dir == 'N')
		player->dir = 3 * PI / 2;
	else if (data->map_dir == 'E')
		player->dir = 0;
	else if (data->map_dir == 'S')
		player->dir = PI / 2;
	else if (data->map_dir == 'W')
		player->dir = PI;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->turn_left = false;
	player->turn_right = false;
	player->dash = 1;
	return (player);
}

int	key_press(int keycode, t_data *data)
{
	/*printf("Keycode: %d\n", keycode);*/
	if (keycode == ESC)
		bruh(data, "Exit game", 0);
	if (keycode == UP || keycode == W)
		data->player->key_up = true;
	if (keycode == DOWN || keycode == S)
		data->player->key_down = true;
	if (keycode == Q)
		data->player->key_left = true;
	if (keycode == E)
		data->player->key_right = true;
	if (keycode == LEFT || keycode == A)
		data->player->turn_left = true;
	if (keycode == RIGHT || keycode == D)
		data->player->turn_right = true;
	/*if (keycode == R)*/
	/*	color_screen(data, 0xFFFF0000);*/
	/*if (keycode == G)*/
	/*	color_screen(data, 0xFF00FF00);*/
	/*if (keycode == B)*/
	/*	color_screen(data, 0xFF0000FF);*/
	if (keycode == M)
		printarr(data->map);
	if (keycode == SHIFT)
		data->player->dash = 2;
	if (keycode == CTRL)
		data->player->dash = 0.1;
	if (keycode == ZERO)
		data->d = 0;
	if (keycode == ONE)
		data->d = 1;
	if (keycode == TWO)
		data->d = 2;
	if (keycode == THREE)
		data->d = 3;
	if (keycode == FOUR)
		data->d = 4;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	/*printf("Keycode: %d\n", keycode);*/
	if (keycode == UP || keycode == W)
		data->player->key_up = false;
	if (keycode == DOWN || keycode == S)
		data->player->key_down = false;
	if (keycode == Q)
		data->player->key_left = false;
	if (keycode == E)
		data->player->key_right = false;
	if (keycode == LEFT || keycode == A)
		data->player->turn_left = false;
	if (keycode == RIGHT || keycode == D)
		data->player->turn_right = false;
	if (keycode == SHIFT)
		data->player->dash = 1;
	if (keycode == CTRL)
		data->player->dash = 1;
	return (0);
}

float	wall(t_data *data, float x, float y, float speed)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / VOX);
	map_y = (int)(y / VOX);
	if (map_x < 0 || map_x >= data->map_width
		|| map_y < 0 || map_y >= data->map_height)
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	return (speed);
}

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

void	move_player(t_data *data)
{
	t_player	*pl;
	float 		speed;
	float 		t_speed;
	double 		x_spd;
	double 		y_spd;

	pl = data->player;
	/*double cos_d;*/
	/*double sin_d;*/
	/*cos_d = cos(pl->dir);*/
	/*sin_d = sin(pl->dir);*/

	t_speed = (float)TURN_SPEED * data->time->delta / 1000;
	if (pl->turn_left)
		pl->dir -= t_speed;
	else if (pl->turn_right)
		pl->dir += t_speed;
	if (pl->dir > 2 * PI)
		pl->dir = 0;
	else if (pl->dir < 0)
		pl->dir = 2 * PI;
	speed = (float)SPEED * data->time->delta / 1000;
	x_spd = speed * cos(pl->dir) * pl->dash;
	y_spd = speed * sin(pl->dir) * pl->dash;
	/*update_player_distance(data, pl);*/
	// printf("X: %f Y: %f X_spd: %f Y_spd: %f\n", pl->x, pl->y, x_spd, y_spd);
	int		check;
	if (pl->key_up)
	{
		// pl->x += wall(data, pl->x + (17 * (1 - 2 * (x_spd < 0))), pl->y, x_spd);
		// pl->y += wall(data, pl->x, pl->y + (17 * (1 - 2 * (y_spd < 0)))  , y_spd);
		check = 15 * (1 - 2 * (x_spd < 0));
		if (data->map[(int)(pl->y / VOX)][(int)(pl->x + check) / VOX] != '1')
			pl->x += wall(data, pl->x + x_spd * 2, pl->y, x_spd);
		check = 15 * (1 - 2 * (y_spd < 0));
		if (data->map[(int)((pl->y + check) / VOX)][(int)(pl->x / (float)VOX)] != '1')
			pl->y += wall(data, pl->x, pl->y + y_spd * 2, y_spd);
		// pl->x += x_spd;
		// pl->y += y_spd;
		/*pl->x += x_spd * (pl->x_dist > 10);*/
		/*pl->y += y_spd * (pl->y_dist > 10);*/
		/*if (data->map[(int)(pl->y / VOX)][(int)(pl->x / VOX)] == '1')*/
		/*{*/
		/*	pl->x -= x_spd;*/
		/*	pl->y -= y_spd;*/
		/*}*/
	}
	else if (pl->key_down)
	{
		// pl->x -= wall(data, pl->x - (17 * (1 - 2 * (x_spd < 0))), pl->y, x_spd);
		// pl->y -= wall(data, pl->x, pl->y - (17 * (1 - 2 * (y_spd < 0))), y_spd);
		pl->x -= wall(data, pl->x - x_spd * 2, pl->y, x_spd);
		pl->y -= wall(data, pl->x, pl->y - y_spd * 2, y_spd);

		/*pl->x -= x_spd * (pl->x_dist > 10);*/
		/*pl->y -= y_spd * (pl->y_dist > 10);*/
		/*if (data->map[(int)(pl->y / VOX)][(int)(pl->x / VOX)] == '1')*/
		/*{*/
		// pl->x += x_spd;
		// pl->y += y_spd;
		/*}*/
	}
	else if (pl->key_left)
	{
		// pl->x += wall(data, pl->x + (17 * (1 - 2 * (y_spd < 0))), pl->y, y_spd);
		// pl->y -= wall(data, pl->x, pl->y - (17 * (1 - 2 * (x_spd < 0))), x_spd);
		pl->x += wall(data, pl->x + y_spd * 2, pl->y, y_spd);
		pl->y -= wall(data, pl->x, pl->y - x_spd * 2, x_spd);
		/*pl->x += y_spd * (pl->x_dist > 10);*/
		/*pl->y -= x_spd * (pl->y_dist > 10);*/
	}
	else if (pl->key_right)
	{
		// pl->x -= wall(data, pl->x - (17 * (1 - 2 * (y_spd < 0))), pl->y, y_spd);
		// pl->y += wall(data, pl->x, pl->y + (17 * (1 - 2 * (x_spd < 0))), x_spd);
		pl->x -= wall(data, pl->x - y_spd * 2, pl->y, y_spd);
		pl->y += wall(data, pl->x, pl->y + x_spd * 2, x_spd);
		/*pl->x -= y_spd * (pl->x_dist > 10);*/
		/*pl->y += x_spd * (pl->y_dist > 10);*/
	}
	// cheat(data, pl, x_spd, y_spd);
	/*printf("X: %f Y: %f x_dist: %f y_dist: %f\n", pl->x, pl->y, pl->x_dist, pl->y_dist);*/
	/*printf("X: %f Y: %f Dir: %f Cos: %f Sin: %f\n", pl->x, pl->y, pl->dir, cos_d, sin_d);*/
	/*if (data->player->key_up && data->player->y > 0 + 4)*/
	/*	data->player->y -= speed * data->player->dash;*/
	/*if (data->player->key_down && data->player->y < HEIGHT - 4)*/
	/*	data->player->y += speed * data->player->dash;*/
	/*if (data->player->key_left && data->player->x > 0 + 4)*/
	/*	data->player->x -= speed * data->player->dash;*/
	/*if (data->player->key_right && data->player->x < WIDTH - 4)*/
	/*	data->player->x += speed * data->player->dash;*/
}
