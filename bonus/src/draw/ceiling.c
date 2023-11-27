/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:40:14 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/27 18:06:27 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint32_t	darken_color(uint32_t color, float factor);

void	draw_ceiling(t_data *data, int x, int end, uint32_t color)
{
	int		y;
	float	factor;
	float	step;

	y = 0;
	factor = 0.5;
	step = factor / (data->game.height / 2);
	while (y < end)
	{
		mlx_put_pixel(data->image, x, y, darken_color(color, factor));
		factor -= step;
		y++;
	}
}
