/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:16:24 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/13 12:33:09 by oohnivch         ###   ########.fr       */
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
	/*player->dir = PI / 2 * 3;*/
	player->dir = 0;
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
	if (keycode == R)
		color_screen(data, 0xFFFF0000);
	if (keycode == G)
		color_screen(data, 0xFF00FF00);
	if (keycode == B)
		color_screen(data, 0xFF0000FF);
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

void	move_player(t_data *data)
{
	t_player	*pl;
	float 		speed;
	float 		t_speed;
	double 		x_spd;
	double 		y_spd;

	pl = data->player;
	t_speed = (float)TURN_SPEED * data->time->delta / 1000;
	speed = (float)SPEED * data->time->delta / 1000;
	x_spd = speed * cos(pl->dir) * pl->dash;
	y_spd = speed * sin(pl->dir) * pl->dash;
	/*double cos_d;*/
	/*double sin_d;*/
	/*cos_d = cos(pl->dir);*/
	/*sin_d = sin(pl->dir);*/

	if (pl->turn_left)
		pl->dir -= t_speed * pl->dash;
	else if (pl->turn_right)
		pl->dir += t_speed * pl->dash;
	if (pl->dir > 2 * PI)
		pl->dir = 0;
	else if (pl->dir < 0)
		pl->dir = 2 * PI;
	if (pl->key_up)
	{
		if (!coll(data, (pl->x + x_spd * 3), (pl->y + y_spd * 3)))
		{
			pl->x += x_spd;
			pl->y += y_spd;
		}
	}
	if (pl->key_down)
	{
		if (!coll(data, (pl->x - x_spd * 3), (pl->y - y_spd * 3)))
		{
			pl->x -= x_spd;
			pl->y -= y_spd;
		}
	}
	if (pl->key_left)
	{
		if (!coll(data, (pl->x + y_spd * 3), (pl->y - x_spd * 3)))
		{
			pl->x += y_spd;
			pl->y -= x_spd;
		}
	}
	if (pl->key_right)
	{
		if (!coll(data, (pl->x - y_spd * 3), (pl->y + x_spd * 3)))
		{
			pl->x -= y_spd;
			pl->y += x_spd;
		}
	}
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
