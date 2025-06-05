/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/05 08:48:24 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_up_game(t_data *data, t_file *file, t_textures *tx, t_time *time)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(file, sizeof(t_file));
	ft_bzero(tx, sizeof(t_textures));
	ft_bzero(time, sizeof(t_time));
	data->file = file;
	data->tx = tx;
	file->tx = tx;
	data->time = time;
}
