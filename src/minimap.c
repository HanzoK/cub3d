/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2.15/06/02 12:44:16 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 15:41:52 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	out_of_bounds(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map_w * VOX || y >= data->map_h * VOX)
		return (true);
	if (data->map[y / VOX][x / VOX] == ' ')
		return (true);
	return (false);
}

void	draw_minimap(t_data *data, float off_x, float off_y)
{
	(void)(off_x + off_y + sizeof(data));
	return ;
}
