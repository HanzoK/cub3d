/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:01:08 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/12 17:02:23 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_partial_map(char **map, int rows)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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

void	*free_texture(t_data *data, t_texture *texture)
{
	(void)data;
	if (!texture)
		return (NULL);
	if (texture->img)
		mlx_destroy_image(data->mlx, texture->img);
	if (texture->split_texture)
		free(texture->split_texture);
	free(texture);
	return (NULL);
}

void	free_textures(t_data *data)
{
	t_textures	*tx;

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
	if (tx->ceiling)
		ft_free(&tx->ceiling);
	if (tx->colour_floor)
		free_array(tx->colour_floor);
	if (tx->colour_ceiling)
		free_array(tx->colour_ceiling);
	tx->north = free_texture(data, tx->north);
	tx->south = free_texture(data, tx->south);
	tx->west = free_texture(data, tx->west);
	tx->east = free_texture(data, tx->east);
}

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		(ft_putstr_fd(s, 2), ft_putstr_fd("\n", 2));
	if (data)
	{
		free_textures(data);
		free_player_sprites(data);
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
