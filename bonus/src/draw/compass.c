/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:31:11 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/02 10:58:28 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	normalize_angle(float angle)
{
	return (angle);
}

void	draw_compass(t_data *data)
{
	t_fvec	diff;
	t_fvec	s;
	t_fvec	e;
	float	angle;

	diff.x = data->goal->pos.x - data->player->pos.x; 
	diff.y = data->goal->pos.y - data->player->pos.y; 
	//printf("pa = %f\n", data->player->angle);
	angle = normalize_angle(get_angle_diff(data->player->angle, get_sprite_angle(diff)));
	//angle = get_sprite_angle(diff);
	angle = fix_angle(3 * M_PI / 2 - angle);
	//printf("angle = %f\n", angle * 180 / M_PI);
	s.x = data->game->width / 2;
	s.y = data->game->height - 51;
	e.x = s.x + 10 * cos(angle);
	e.y = s.y + 10 * sin(angle);
	draw_line(data, s, e, 0xFF0000FF);
}
