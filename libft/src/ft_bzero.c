/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:55:52 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:52:50 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Writes n zeroed bytes to the string s.
// If n is zero, ft_bzero() does nothing.
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
