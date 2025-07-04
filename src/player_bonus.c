/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:16:24 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/11 22:05:16 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*init_player(t_data *data)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
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
	if (keycode == ESC)
		bruh(data, "Exit game", 0);
	if (keycode == UP || keycode == W)
		data->player->key_up = true;
	if (keycode == DOWN || keycode == S)
		data->player->key_down = true;
	if (keycode == Q)
		data->player->turn_left = true;
	if (keycode == E)
		data->player->turn_right = true;
	if (keycode == LEFT || keycode == A)
		data->player->key_left = true;
	if (keycode == RIGHT || keycode == D)
		data->player->key_right = true;
	if (keycode == SHIFT)
		data->player->dash = 2;
	if (keycode == ALT)
	{
		if (data->mouse_enabled)
		{
			data->mouse_enabled = false;
			mlx_mouse_show(data->mlx, data->win);
		}
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == UP || keycode == W)
		data->player->key_up = false;
	if (keycode == DOWN || keycode == S)
		data->player->key_down = false;
	if (keycode == Q)
		data->player->turn_left = false;
	if (keycode == E)
		data->player->turn_right = false;
	if (keycode == LEFT || keycode == A)
		data->player->key_left = false;
	if (keycode == RIGHT || keycode == D)
		data->player->key_right = false;
	if (keycode == SHIFT)
		data->player->dash = 1;
	if (keycode == ALT)
	{
		data->mouse_enabled = true;
		mlx_mouse_hide(data->mlx, data->win);
		mlx_mouse_move(data->mlx, data->win,
			data->window_center_x, data->window_center_y);
	}
	return (0);
}

void	turn(t_data *data, t_player *pl)
{
	if (pl->turn_left)
		pl->dir -= (float)TURN_SPEED * data->time->delta / 1000;
	else if (pl->turn_right)
		pl->dir += (float)TURN_SPEED * data->time->delta / 1000;
	if (pl->dir > 2 * PI)
		pl->dir = 0;
	else if (pl->dir < 0)
		pl->dir = 2 * PI;
}

void	move_player(t_data *data)
{
	t_player	*pl;
	float		speed;
	double		x_spd;
	double		y_spd;

	pl = data->player;
	turn(data, pl);
	speed = (float)SPEED * data->time->delta / 1000;
	x_spd = speed * cos(pl->dir) * pl->dash;
	y_spd = speed * sin(pl->dir) * pl->dash;
	if (pl->key_up)
		walk_forward(data, pl, x_spd, y_spd);
	else if (pl->key_down)
		walk_backward(data, pl, x_spd, y_spd);
	if (pl->key_left)
		strafe_left(data, pl, x_spd, y_spd);
	else if (pl->key_right)
		strafe_right(data, pl, x_spd, y_spd);
}
