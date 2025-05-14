/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/14 13:59:44 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_up_game(t_data *data, t_file *file, t_textures *tx, t_time *time)
{
	ft_bzero(data, sizeof(*data));
	ft_bzero(file, sizeof(*file));
	ft_bzero(tx, sizeof(*tx));
	ft_bzero(time, sizeof(*time));
	data->file = file;
	file->tx = tx;
	data->time = time;
}
