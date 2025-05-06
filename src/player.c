/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:16:24 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/06 17:20:21 by oohnivch         ###   ########.fr       */
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
	player->dir = PI / 2 * 3;
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
	printf("Keycode: %d\n", keycode);
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
	if (keycode == E)
		evening(data);
	if (keycode == M)
		printarr(data->map);
	if (keycode == SHIFT)
		data->player->dash = 2;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	printf("Keycode: %d\n", keycode);
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
	return (0);
}

void	move_player(t_data *data)
{
	t_player	*player;
	float 		speed;
	float 		turn_speed;
	float		sin_dir;
	float		cos_dir;

	player = data->player;
	turn_speed = (float)TURN_SPEED;
	speed = (float)SPEED;

	if (player->turn_left)
		player->dir -= turn_speed;
	if (player->turn_right)
		player->dir += turn_speed;
	if (player->dir > 2 * PI)
		player->dir = 0;
	if (player->dir < 0)
		player->dir = 2 * PI;
	sin_dir = sin(player->dir);
	cos_dir = cos(player->dir);
	if (player->key_up)
	{
		player->x += speed * cos_dir * player->dash;
		player->y += speed * sin_dir * player->dash;
	}
	if (player->key_down)
	{
		player->x -= speed * cos_dir * player->dash;
		player->y -= speed * sin_dir * player->dash;
	}
	if (player->key_left)
	{
		player->x -= speed * sin_dir * player->dash;
		player->y += speed * cos_dir * player->dash;
	}
	if (player->key_right)
	{
		player->x += speed * sin_dir * player->dash;
		player->y -= speed * cos_dir * player->dash;
	}
	printf("X: %f Y: %f\n", player->x, player->y);
	/*if (data->player->key_up && data->player->y > 0 + 4)*/
	/*	data->player->y -= speed * data->player->dash;*/
	/*if (data->player->key_down && data->player->y < HEIGHT - 4)*/
	/*	data->player->y += speed * data->player->dash;*/
	/*if (data->player->key_left && data->player->x > 0 + 4)*/
	/*	data->player->x -= speed * data->player->dash;*/
	/*if (data->player->key_right && data->player->x < WIDTH - 4)*/
	/*	data->player->x += speed * data->player->dash;*/
}
