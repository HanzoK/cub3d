/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/13 19:04:37 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_up_game(t_data *data)
{
	data->img = NULL;
	data->map = NULL;
	data->width = 0;
	data->height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_direction = NORTH;
}
