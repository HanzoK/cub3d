/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:30:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/16 13:17:42 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_data *data, const char *path, int i, t_sprite *ps)
{
	ps->index = i;
	ps->path = ft_strdup(path);
	if (!ps->path)
		bruh(data, "Error\nSprite path malloc failed\n", 1);
	ps->img = mlx_xpm_file_to_image(data->mlx, ps->path,
			&ps->width, &ps->height);
	if (!ps->img)
		bruh(data, "Error\nSprite image loading failed\n", 1);
	ps->addr = mlx_get_data_addr(ps->img, &ps->bpp,
			&ps->size_line, &ps->endian);
	if (!ps->addr)
		bruh(data, "Error\nSprite address loading failed\n", 1);
	split_sprite_texture(ps);
	if (!ps->split_texture)
		bruh(data, "Error\nSprite split texture failed\n", 1);
	return ;
}

void	set_idle_sprite(t_data *data)
{
	char		path[1024];
	t_sprite	*ps;

	snprintf(path, sizeof(path), "./textures/idle/%04d.xpm", 1);
	ps = ft_calloc(1, sizeof(t_sprite));
	if (!ps)
		bruh(data, "Error\nSprite malloc failed\n", 1);
	data->player->anim[IDLE] = ps;
	ps->next = data->player->anim[IDLE];
	ps->next = ps;
	init_sprite(data, path, 1, ps);
}

void	set_walk_sprite(t_data *data)
{
	char		path[1024];
	t_sprite	*ps;
	t_sprite	*last_ps;
	int			i;

	i = 1;
	last_ps = NULL;
	while (i < 30)
	{
		snprintf(path, sizeof(path), "./textures/walk/%04d.xpm", i);
		ps = ft_calloc(1, sizeof(t_sprite));
		if (!ps)
			bruh(data, "Error\nWalk Sprite init failed\n", 1);
		if (!data->player->anim[WALK])
			data->player->anim[WALK] = ps;
		else
			if (last_ps)
				last_ps->next = ps;
		last_ps = ps;
		ps->next = data->player->anim[WALK];
		init_sprite(data, path, i, ps);
		i++;
	}
}

void	set_fire_sprite(t_data *data)
{
	char		path[1024];
	t_sprite	*ps;
	t_sprite	*last_ps;
	int			i;

	i = 1;
	last_ps = NULL;
	while (i < 8)
	{
		snprintf(path, sizeof(path), "./textures/fire/%04d.xpm", i);
		ps = ft_calloc(1, sizeof(t_sprite));
		if (!ps)
			bruh(data, "Error\nFire Sprite init failed\n", 1);
		if (!data->player->anim[FIRE])
			data->player->anim[FIRE] = ps;
		else
			if (last_ps)
				last_ps->next = ps;
		last_ps = ps;
		ps->next = data->player->anim[FIRE];
		init_sprite(data, path, i, ps);
		i++;
	}
}

void	set_player_sprites(t_data *data)
{
	set_idle_sprite(data);
	set_walk_sprite(data);
	set_fire_sprite(data);
}
