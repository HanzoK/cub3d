/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:03 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/01 14:51:34 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	split_texture(t_texture *tx)
{
	char	**split_texture;
	int		y;

	y = 0;
	split_texture = ft_calloc(sizeof(char *), tx->height + 1);
	if (!split_texture)
		return ;
	while (y < tx->height)
	{
		split_texture[y] = tx->addr + (y * tx->size_line);
		y++;
	}
	tx->split_texture = split_texture;
}

t_texture	*init_texture(t_data *data, char *path, t_texture **ptr)
{
	t_texture	*tx;
	size_t		len;
	char		*str;

	str = ft_strrchr(path, '/');
	str += (str != NULL) + ((str == NULL) * (size_t)path);
	len = ft_strlen(str);
	if (len < 5 || ft_strncmp(str + len - 4, ".xpm", 4) != 0)
		return (bruh(data, "\nError\nEver heard of .xpm files?\n", 1), NULL);
	tx = ft_calloc(1, sizeof(t_texture));
	if (!tx)
		bruh(data, "Error\ntexture malloc failed\n", 1);
	*ptr = tx;
	tx->img = mlx_xpm_file_to_image(data->mlx, path, &tx->width, &tx->height);
	if (!tx->img)
		bruh(data, "Error\ntexture loading failed\n", 1);
	tx->addr = mlx_get_data_addr(tx->img,
			&tx->bpp, &tx->size_line, &tx->endian);
	if (!tx->addr)
		bruh(data, "Error\ntexture address failed\n", 1);
	split_texture(tx);
	if (!tx->split_texture)
		bruh(data, "Error\ntexture split failed\n", 1);
	return (tx);
}

int	load_textures(t_data *data)
{
	data->tx->north = init_texture(data,
			data->tx->north_path, &data->tx->north);
	write(1, "\rLOADING TEXTURES [1/4]", 23);
	data->tx->south = init_texture(data,
			data->tx->south_path, &data->tx->south);
	write(1, "\rLOADING TEXTURES [2/4]", 23);
	data->tx->west = init_texture(data,
			data->tx->west_path, &data->tx->west);
	write(1, "\rLOADING TEXTURES [3/4]", 23);
	data->tx->east = init_texture(data,
			data->tx->east_path, &data->tx->east);
	write(1, "\rLOADING TEXTURES [4/4]\n", 24);
	printf("Textures loaded\n");
	return (1);
}
