/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:58:16 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 07:57:30 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	get_time(t_data *data)
{
	struct timeval	time_var;
	int				check;
	long			time;

	check = gettimeofday(&time_var, NULL);
	if (check == -1)
		bruh(data, "Error: gettimeofday failed", 1);
	time = time_var.tv_sec * 1000 + time_var.tv_usec / 1000;
	if (time < 0)
		bruh(data, "Error: gettimeofday failed", 1);
	return (time);
}

long	get_delta_time(t_data *data)
{
	data->time->curr = get_time(data);
	data->time->delta = data->time->curr - data->time->last;
	data->time->last = data->time->curr;
	return (data->time->delta);
}
