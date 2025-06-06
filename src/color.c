/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:01:44 by oohnivch          #+#    #+#             */
/*   Updated: 2025/06/05 07:57:17 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	shade_color(float dist, int color)
{
	int		alpha;
	int		red;
	int		green;
	int		blue;
	float	ratio;

	alpha = (color >> 24) & 0xFF;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	ratio = dist / DRAW_DIST;
	red = (int)((float)red * (1 - ratio));
	green = (int)((float)green * (1 - ratio));
	blue = (int)((float)blue * (1 - ratio));
	if (red <= 0)
		red = 1;
	if (green <= 0)
		green = 1;
	if (blue <= 0)
		blue = 1;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}
