/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:21:28 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/11 18:38:23 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_all_three(char **colours)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		ft_free(&colours[i]);
		i++;
	}
	return (0);
}

void	free_sprite_list(t_data *data, t_sprite **first)
{
	t_sprite	*current;
	t_sprite	*next;

	current = *first;
	while (current)
	{
		next = current->next;
		if (current->img)
			mlx_destroy_image(data->mlx, current->img);
		if (current->split_texture)
			free(current->split_texture);
		if (current->path)
			ft_free(&current->path);
		free(current);
		current = next;
	}
	*first = NULL;
}

void	free_player_sprites(t_data *data)
{
	if (!data->player)
		return ;
	free_sprite_list(data, &data->player->anim[IDLE]);
	free_sprite_list(data, &data->player->anim[WALK]);
	free_sprite_list(data, &data->player->anim[FIRE]);
}
