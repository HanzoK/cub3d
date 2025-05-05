/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:03:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/05 13:49:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_textures(t_data *data)
{
	t_tx *tx;

	tx = data->file->tx;
	if (!tx)
		return ;
	if (tx->north)
		ft_free(&tx->north);
	if (tx->south)
		ft_free(&tx->south);
	if (tx->west)
		ft_free(&tx->west);
	if (tx->east)
		ft_free(&tx->east);
	if (tx->floor)
		ft_free(&tx->floor);
	if	(tx->sprite)
		ft_free(&tx->sprite);
	if (tx->ceiling)
		ft_free(&tx->ceiling);
	if (tx->colour_floor)
		free_array(tx->colour_floor);
	if (tx->colour_ceiling)
		free_array(tx->colour_ceiling);
}

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		(ft_putstr_fd(s, 2), ft_putstr_fd("\n", 2));
	if (data)
	{
		free_array(data->map);
		free_array(data->file->file);
		free_textures(data);
		//free(data);
		data = NULL;
	}
	exit(status);
}
