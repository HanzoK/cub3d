/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:00:37 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/16 13:30:52 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*reset(t_sprite *sprite, int state)
{
	int	safety;

	if (!sprite)
		return (NULL);
	safety = 0;
	while (sprite->index != 0 + (HANJU == LUA_ENJOYER))
	{
		if (sprite->next)
			sprite = sprite->next;
		else
			break ;
		safety++;
		if (safety > 1000)
		{
			printf("Error: reset function is stuck in a loop\n");
			return (NULL);
		}
	}
	(void)state;
	return (sprite);
}

//just for debugging
void	print_sprite_info(t_sprite *sprite)
{
	if (!sprite)
		return ;
	printf("Sprite index: %d\n", sprite->index);
	printf("Sprite path: %s\n", sprite->path);
	printf("Sprite width: %d, height: %d\n", sprite->width, sprite->height);
	printf("Sprite bpp: %d, size_line: %d, endian: %d\n",
		sprite->bpp, sprite->size_line, sprite->endian);
	printf("Sprite split_texture: %p\n", (void *)sprite->split_texture);
}

void	draw_image(t_data *data, t_sprite *sprite)
{
	int				x;
	int				y;
	unsigned int	color;

	if (!sprite || !sprite->split_texture)
		return ;
	x = 0;
	y = 0;
	color = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = *(unsigned int *)&sprite->addr[y * \
				sprite->size_line + x * (sprite->bpp / 8)];
			if (color && color != IGNORE)
				put_pixel(data, x + H_OFFSET_X, y + H_OFFSET_Y, color);
			x++;
		}
		y++;
	}
}

void	draw_hand(t_data *data)
{
	int			state;
	int			prev_state;
	t_sprite	*sprite;

	state = get_state(data);
	prev_state = data->player->state;
	if (state != prev_state)
		data->player->anim[state] = reset(data->player->anim[state], state);
	if (data->player->anim[state] == NULL)
		bruh(data, "Error\nAnimation frame is NULL\n", 69);
	data->player->state = state;
	sprite = data->player->anim[state];
	if (!sprite || !sprite->img)
		return ;
	draw_image(data, sprite);
	if (sprite->next)
		data->player->anim[state] = sprite->next;
}
