/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:03:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/14 20:18:04 by oohnivch         ###   ########.fr       */
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
	t_textures *tx;

	tx = data->tx;
	if (!tx)
		return ;
	if (tx->north_path)
		ft_free(&tx->north_path);
	if (tx->south_path)
		ft_free(&tx->south_path);
	if (tx->west_path)
		ft_free(&tx->west_path);
	if (tx->east_path)
		ft_free(&tx->east_path);
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
	mlx_destroy_image(data->mlx, tx->north->img);
	mlx_destroy_image(data->mlx, tx->south->img);
	mlx_destroy_image(data->mlx, tx->west->img);
	mlx_destroy_image(data->mlx, tx->east->img);
	free(tx->north);
	free(tx->south);
	free(tx->west);
	free(tx->east);
}

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		(ft_putstr_fd(s, 2), ft_putstr_fd("\n", 2));
	if (data)
	{
		free_textures(data);
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			(mlx_destroy_display(data->mlx), free(data->mlx));
		free_array(data->map);
		free_array(data->file->file);
		free(data->player);
		data = NULL;
	}
	exit(status);
}
