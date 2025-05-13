/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:23:32 by hanjkim           #+#    #+#             */
/*   Updated: 2025/05/13 16:44:42 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	button_hook(t_data *data)
{
	bruh(data, NULL, 0);
	return (0);
}

char	*join2(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	return (ptr);
}

void	printarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int	get_color(int red, int green, int blue)
{
	int	color;

	color = 255;
	color <<= 8;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	return (color);
}

/*float	dist(float *start, float *end, float direction)*/
/*{*/
/*	float	x;*/
/*	float	y;*/
/*	float	angle;*/
/**/
/*	x = end[0] - start[0];*/
/*	y = end[1] - start[1];*/
/*	angle = atan2f(y, x) - direction;*/
/*	return (sqrtf(powf(x, 2) + powf(y, 2)) * cosf(angle));*/
/*}*/
