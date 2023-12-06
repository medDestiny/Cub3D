/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:37:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/05 19:23:22 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	get_sprite_angle(t_fvec diff)
{
	float	alpha;

	alpha = atan2(diff.y, diff.x);
	return (fix_angle(alpha));
}

float	get_angle_diff(float pa, float alpha)
{
	float	diff;

	diff = pa - alpha;
	if (pa > 3 * M_PI / 2 && alpha < M_PI / 2)
		diff -= 2 * M_PI;
	else if (pa < M_PI / 2 && alpha > 3 * M_PI / 2)
		diff += 2 * M_PI;
	return (diff);
}

void	sp_get_data(t_data *data, t_sprite *sp, t_sp_data *sp_data)
{
	t_fvec	diff;
	float	alpha;
	float	sa;
	float	scr_angle;
	float	ratio;

	diff.x = sp->pos.x - data->player->pos.x;
	diff.y = sp->pos.y - data->player->pos.y;
	alpha = get_sprite_angle(diff);
	sp_data->distance = sqrt(diff.x * diff.x + diff.y * diff.y);
	if (sp_data->distance == 0)
		sp_data->distance = 1;
	sp_data->size = (float)(data->game->height * UNIT) / sp_data->distance;
	sa = get_angle_diff(data->player->angle, alpha);
	scr_angle = (FOV / 2) - (sa * 180 / M_PI);
	ratio = (float)data->game->width / FOV;
	sp_data->x = scr_angle * ratio;
}

void	sp_stripe_data(t_stripe *s, t_data *data, t_sp_data *sp_data)
{
	s->draw_s = data->game->height / 2 - sp_data->size / 2;
	s->draw_e = data->game->height / 2 + sp_data->size / 2;
	s->yoffset = 0;
	if (s->draw_s < 0)
		s->draw_s = 0;
	if (s->draw_e >= (int)data->game->height)
	{
		if (s->draw_e > (int)data->game->height)
			s->yoffset = (s->draw_e - data->game->height) * s->y_step;
		s->draw_e = data->game->height - 1;
	}
}
