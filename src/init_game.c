/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/05 13:58:35 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_up_game(t_data *data, t_file *file, t_tx *tx)
{
	ft_bzero(data, sizeof(*data));
	ft_bzero(file, sizeof(*file));
	ft_bzero(tx, sizeof(*tx));
	data->file = file;
	file->tx = tx;
}
