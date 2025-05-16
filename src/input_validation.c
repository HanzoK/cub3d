/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:05:44 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/16 15:01:39 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_validation(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nAre you sure you know what you're doing?\n", 2);
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nDo you know the definition of insanity?\n", 2);
		exit (1);
	}
}

int	is_valid_map_char(char c)
{
	if (c != '0'
	&&	c != '1'
	&&	c != 'N'
	&&	c != 'S'
	&&	c != 'E'
	&&	c != 'W'
	&&	c != ' ')
		return (0);
	return (1);
}

int	check_map_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!is_valid_map_char(data->map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_data *data)
{
	int		i;
	int		j;
	int		pc;
	char	c;

	if (!check_map_chars(data))
		return (0);
	pc = 0;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			c = data->map[i][j];
			if (c == '0')
			{
				if (i == 0 || i == data->map_height - 1 || j == 0
				|| j == data->map_width - 1)
					return (false);
				if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' '
				|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
					return (false);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data->player_x = j;
				data->player_y = i;
				pc++;
			}
			j++;
		}
		i++;
	}
	if (pc == 1)
		return (1);
	else
		return (0);
}

int	rgb_value_check (char **colours)
{
	int		r;
	int		g;
	int		b;
	int 	i;
	char	*temp;

	if (!colours || !colours[0] || !colours[1] || !colours[2])
		return (0);
	i = -1;
	while (++i < 3)
	{
		temp = ft_strtrim(colours[i], " \t\n");
		ft_free(&colours[i]);
		colours[i] = temp;
		if (!is_numeric_value(temp))
			return (0);
	}
	r = ft_atoi(colours[0]);
	g = ft_atoi(colours[1]);
	b = ft_atoi(colours[2]);
	if (!((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
		&& (b >= 0 && b <= 255)))
		return (0);
	else
		return (1);
}

t_texture	*init_texture(t_data *data, char *path, t_texture **ptr)
{
	t_texture	*tx;

	tx = ft_calloc(1, sizeof(t_texture));
	if (!tx)
		bruh(data, "Error\ntexture malloc failed\n", 1);
	*ptr = tx;
	tx->img = mlx_xpm_file_to_image(data->mlx, path, &tx->width, &tx->height);
	if (!tx->img)
		bruh(data, "Error\ntexture loading failed\n", 1);
	tx->addr = mlx_get_data_addr(tx->img, &tx->bpp, &tx->size_line, &tx->endian);
	if (!tx->addr)
		bruh(data, "Error\ntexture address failed\n", 1);
	split_texture(tx);
	if (!tx->split_texture)
		bruh(data, "Error\ntexture split failed\n", 1);
	return (tx);
}

int	load_textures(t_data *data)
{
	data->tx->north = init_texture(data, data->tx->north_path, &data->tx->north);
	write(1, "\rLOADING TEXTURES [1/4]", 23);
	data->tx->south = init_texture(data, data->tx->south_path, &data->tx->south);
	write(1, "\rLOADING TEXTURES [2/4]", 23);
	data->tx->west = init_texture(data, data->tx->west_path, &data->tx->west);
	write(1, "\rLOADING TEXTURES [3/4]", 23);
	data->tx->east = init_texture(data, data->tx->east_path, &data->tx->east);
	write(1, "\rLOADING TEXTURES [4/4]\n", 24);
	printf("Textures loaded\n");
	return (1);
}

/*bool	validate_xpm_64(t_data *data, void *mlx)*/
/*{*/
/*	int		w;*/
/*	int		h;*/
/*	void	*img;*/
/*	size_t	len;*/
/**/
/*	len = ft_strlen(path);*/
/*	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)*/
/*		return (false);*/
/*	data->file->tx->north.img = mlx_xpm_file_to_image(mlx, data->file->tx->north_path, &w, &h);*/
/*	data->file->tx->south.img = mlx_xpm_file_to_image(mlx, data->file->tx->south_path, &w, &h);*/
/*	data->file->tx->east.img = mlx_xpm_file_to_image(mlx, data->file->tx->east_path, &w, &h);*/
/*	data->file->tx->south.img = mlx_xpm_file_to_image(mlx, data->file->tx->west_path, &w, &h);*/
/*	if (!data->file->tx->north*/
/*		|| !data->file->tx->south*/
/*		|| !data->file->tx->east*/
/*		|| !data->file->tx->west)*/
/*		return (false);*/
/*	return (true);*/
/*}*/
