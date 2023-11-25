/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:39:39 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:42:58 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_floor(t_data *data, int x, int start, uint32_t color)
{
	int	y;

	y = start;
	while (y < (int)data->game.height)
	{
		mlx_put_pixel(data->image_p, x, y, color);
		y++;
	}
}
