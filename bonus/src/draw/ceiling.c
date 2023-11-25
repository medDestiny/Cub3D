/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:40:14 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:42:53 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceiling(t_data *data, int x, int end, uint32_t color)
{
	int	y;

	y = 0;
	while (y < end)
	{
		mlx_put_pixel(data->image_p, x, y, color);
		y++;
	}
}
