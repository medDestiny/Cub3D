/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:28 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/26 12:25:21 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_hud(t_data *data)
{
	t_ivec		pos;
	t_fvec		step;
	t_fvec		offset;
	uint32_t	color;
	uint32_t	*texture;

	texture = (uint32_t *)h->pixels;
	step.x = (float)h->width / data->game.width;
	step.y = (float)h->height / data->game.height;
	pos.x = -1;
	offset.x = 0;
	while (++pos.x < (int)data->game.width)
	{
		pos.y = -1;
		offset.y = 0;
		while (++pos.y < (int)data->game.height)
		{
			color = rev_bits(texture[(int)offset.x + (int)offset.y * h->width]);
			if ((color << 24) != 0)
				mlx_put_pixel(data->image, pos.x, pos.y, color);
			offset.y += step.y;
		}
		offset.x += step.x;
	}
}
