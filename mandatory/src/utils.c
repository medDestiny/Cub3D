/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:05:19 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/26 11:56:04 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall(char pos)
{
	if (pos != '0' && pos != 'W' && pos != 'E' && pos != 'N' && pos != 'S')
		return (1);
	return (0);
}

void	get_dir_vector(float *x, float *y, float angle)
{
	*x = cos(angle);
	*y = sin(angle);
}

float	fix_angle(float angle)
{
	if (angle < 0)
		return (angle + M_PI * 2);
	else if (angle > 2 * M_PI)
		return (angle - M_PI * 2);
	return (angle);
}

t_ivec	fvec_to_ivec(t_fvec x)
{
	return ((t_ivec){(int)x.x, (int)x.y});
}

uint32_t	rev_bits(uint32_t color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	a = (color >> 24) & 0xFF;
	b = (color >> 8) & 0xFF00;
	g = (color << 8) & 0xFF0000;
	r = (color << 24) & 0xFF000000;
	return (r | g | b | a);
}
