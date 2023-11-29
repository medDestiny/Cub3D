/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:18:01 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 10:18:15 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_game(t_data *data)
{
	t_sp_list	*sp;

	//draw_player(data->image_p, data->player);
	//draw_circle(data->image_p, data->enemy->pos, 5, 0x111111FF);
	draw_scene(data);
	sp = data->sprites;
	while (sp)
	{
		if (sp->sp->state == ACTIVE)
			draw_sprite(data, sp->sp);
		sp = sp->next;
	}
	draw_sprite(data, data->enemy);
	//draw_hud(data);
}
