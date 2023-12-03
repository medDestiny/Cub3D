/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:19:02 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 22:01:25 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_minimap	init_data(t_data *data)
{
	t_minimap	m;

	m.ratio.x = data->game->width * 115 / WIN_WID;
	m.ratio.y = data->game->height * 127 / WIN_HEI;
	m.p.x = data->game->width * 40 / WIN_WID;
	m.p.y = data->game->height * 303 / WIN_HEI;
	m.s.x = data->game->width / 2 + m.p.x;
	m.s.y = data->game->height / 2 + m.p.y;
	m.e.x = m.s.x + m.ratio.x;
	m.e.y = m.s.y + m.ratio.y;
	return (m);
}

void	draw_sanity_bar(t_data *data)
{
	t_minimap	m;
	int			max_sanity;
	int			color;
	int			level;

	m = init_data(data);
	max_sanity = SANITY;
	color = 0x222222FF;
	level = (float)(data->player->sanity * m.ratio.y) / max_sanity;
	while (m.s.y < m.e.y)
	{
		if ((int)m.e.y - (int)m.s.y <= level)
			color = 0xDD2222FF;
		draw_line(data, (t_fvec){m.s.x, m.s.y},
			(t_fvec){m.e.x, m.s.y}, color);
		m.s.y++;
	}
}
