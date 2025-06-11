/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:30:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/11 22:15:52 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	split_sprite_texture(t_sprite *tx)
{
	char	**split_texture;
	int		y;

	y = 0;
	/*split_texture = ft_calloc(sizeof(char *), tx->height + 1);*/
	split_texture = ft_calloc(tx->height + 1, sizeof(*split_texture));
	if (!split_texture)
		return ;
	while (y < tx->height)
	{
		split_texture[y] = tx->addr + (y * tx->size_line);
		y++;
	}
	tx->split_texture = split_texture;
}

t_sprite	*init_sprite(t_data *data, const char *path, int i)
{
	t_sprite	*ps;

	ps = ft_calloc(1, sizeof(t_sprite));
	if (!ps)
		bruh(data, "Error\nSprite malloc failed\n", 1);
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
	ft_printf("Sprite %d loaded from %s\n", i, path);
	ft_printf("Sprite width: %d, height: %d\n", ps->width, ps->height);
	ft_printf("Sprite bpp: %d, size_line: %d, endian: %d\n",
		ps->bpp, ps->size_line, ps->endian);
	ft_printf("Sprite split_texture: %p\n", ps->split_texture);
	if (!ps->split_texture)
		bruh(data, "Error\nSprite split texture failed\n", 1);
	ps->next = NULL;
	return (ps);
}

void	set_idle_sprite(t_data *data)
{
	char		path[1024];
	t_sprite	*ps;

	snprintf(path, sizeof(path), "./textures/idle/%04d.xpm", 1);
	ft_printf("Loading idle sprite from %s\n", path);
	ps = init_sprite(data, path, 0);
	ps->next = data->player->anim[IDLE];
	data->player->anim[IDLE] = ps;
}

void	set_walk_sprite(t_data *data)
{
	char		path[1024];
	t_sprite	*ps;
	int			i;

	i = 1;
	while (i < 30)
	{
		snprintf(path, sizeof(path), "./textures/walk/%04d.xpm", i);
		ft_printf("Loading idle sprite from %s\n", path);
		ps = init_sprite(data, path, i);
		ps->next = data->player->anim[WALK];
		data->player->anim[WALK] = ps;
		i++;
	}
}
void	set_fire_sprite(t_data *data)
{
	char		path[1024];
	t_sprite	*ps;
	int			i;

	i = 1;
	while (i < 8)
	{
		snprintf(path, sizeof(path), "./textures/fire/%04d.xpm", i);
		ft_printf("Loading idle sprite from %s\n", path);
		ps = init_sprite(data, path, i);
		ps->next = data->player->anim[FIRE];
		data->player->anim[FIRE] = ps;
		i++;
	}
}

void	set_player_sprites(t_data *data)
{
	set_idle_sprite(data);
	set_walk_sprite(data);
	set_fire_sprite(data);
}
