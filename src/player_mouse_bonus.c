/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:23 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/12 16:45:06 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_click(int button, int x, int y, t_data *data)
{
	(void)(x + y);
	if (button == 1)
		data->player->state = 2;
	return (0);
}
