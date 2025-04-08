/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:06:21 by hanjkim           #+#    #+#             */
/*   Updated: 2025/04/08 21:07:17 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_directions
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}				t_directions;

typedef struct s_data
{
	void	*img;
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		player_dir;
}				t_data;

#endif
