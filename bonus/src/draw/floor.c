/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:39:39 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/27 18:20:41 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint32_t	darken_color(uint32_t color, float factor);

void	draw_floor(t_data *data, int x, int start, uint32_t color)
{
	int		y;
	float	factor;
	float	step;

	y = data->game.height - 1;
	factor = 0.5;
	step = factor / (data->game.height / 2);
	while (y >= start)
	{
		mlx_put_pixel(data->image, x, y, darken_color(color, factor));
		factor -= step;
		y--;
	}
}
