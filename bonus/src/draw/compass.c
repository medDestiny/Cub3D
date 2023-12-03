/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:31:11 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 18:57:05 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static float	get_compass_angle(t_data *data)
{
	t_fvec	diff;
	float	angle;

	diff.x = data->goal->pos.x - data->player->pos.x; 
	diff.y = data->goal->pos.y - data->player->pos.y; 
	angle = get_angle_diff(data->player->angle, get_sprite_angle(diff));
	angle = fix_angle(3 * M_PI / 2 - angle);
	return (angle);
}

static void	get_drawing_coords(t_data *data, t_fvec *s, t_fvec *e, float angle)
{
	t_fvec	ratio;
	float	len;

	ratio.x = data->game->width * 94 / 1280;
	ratio.y = data->game->height * 276 / 960;
	len = (float)(data->game->height * 15) / 960;
	s->x = data->game->width / 2 + ratio.x;
	s->y = data->game->height / 2 + ratio.y;
	e->x = s->x + len * cos(angle);
	e->y = s->y + len * sin(angle);
}

void	draw_compass(t_data *data)
{
	t_fvec	center;
	t_fvec	end;
	float	radius1;
	float	radius2;
	float	angle;

	angle = get_compass_angle(data);
	get_drawing_coords(data, &center, &end, angle);
	radius1 = (float)(data->game->height * 20) / 960;
	radius2 = (float)(data->game->height * 3) / 1280;
	draw_circle(data, center, radius1, 0x00EE00FF);
	draw_line(data, center, end, 0xFF0000FF);
	draw_circle(data, center, radius2, 0xFF0000FF);
}
