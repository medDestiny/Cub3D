/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:18:01 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 19:00:22 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_compass(t_data *data);
void	draw_hud(t_data *data);

void	render_game(t_data *data)
{
	t_sp_list	*sp;

	draw_scene(data);
	sp = data->sprites;
	while (sp)
	{
		if (sp->sp->state == ACTIVE)
			draw_sprite(data, sp->sp);
		sp = sp->next;
	}
	draw_sprite(data, data->goal);
	draw_sprite(data, data->enemy);
	draw_hud(data);
	draw_tablet(data);
	draw_compass(data);
}
