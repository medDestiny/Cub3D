/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:31:11 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 22:36:21 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_compass(t_data *data)
{
	t_fvec	diff;
	t_fvec	ratio;
	t_fvec	s;
	t_fvec	e;
	float	r1;
	float	r2;
	float	r3;
	float	angle;

	diff.x = data->goal->pos.x - data->player->pos.x; 
	diff.y = data->goal->pos.y - data->player->pos.y; 
	ratio.x = data->game->width * 94 / WIN_WID;
	ratio.y = data->game->height * 276 / WIN_HEI;
	r1 = (float)(data->game->height * 15) / WIN_HEI;
	r2 = (float)(data->game->height * 20) / WIN_HEI;
	r3 = (float)(data->game->height * 3) / WIN_HEI;
	angle = get_angle_diff(data->player->angle, get_sprite_angle(diff));
	angle = fix_angle(3 * M_PI / 2 - angle);
	s.x = data->game->width / 2 + ratio.x;
	s.y = data->game->height / 2 + ratio.y;
	e.x = s.x + r1 * cos(angle);
	e.y = s.y + r1 * sin(angle);
	draw_circle(data, s, r2, 0x00EE00FF);
	draw_line(data, s, e, 0xFF0000FF);
	draw_circle(data, s, r3, 0xFF0000FF);
}
