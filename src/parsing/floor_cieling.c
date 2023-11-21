/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cieling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:25:41 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/14 10:16:48 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	merge_rgba(char **colors, t_data *data)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
	int			i;
	
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	a = 255;
	i = 0;
	if (r > 255 | g > 255 | b > 255)
		ft_error(COLOR_RANGE, data);
	return (r | g | b | a);
}

int	ft_arraylen(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	parse_color(char **colors)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (colors[i])
	{
		while (colors[i][d])
		{
			if (ft_isdigit(colors[i][d]) == 1)
				d++;
			else
				return(FLOOR_INV);
		}
		i++;
		d = 0;
	}
	return (0);
}


