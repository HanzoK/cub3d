/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:02:30 by oohnivch          #+#    #+#             */
/*   Updated: 2025/05/05 12:36:10 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "mlx.h"*/
#include <mlx.h>
#include "cub3d.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Kim Chaaa''");
	/*if (!win_ptr)*/
	/*{*/
	/*	mlx_destroy_display(mlx_ptr);*/
	/*	free(mlx_ptr);*/
	/*	return (1);*/
	/*}*/
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	return (0);
}
