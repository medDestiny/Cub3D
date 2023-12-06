/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:43:57 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/06 12:06:32 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * calculated the ratio of the minimap area 
 * depending on the game width and height
 * calculated left and right distances from the mid of the WIDTH
 * calculated the unit depending 
 * on the minimap square (181 at first) 
 * divided by the number of squares we choose to draw
 * (181) minimap initial square unit
 * (156) left initial distance from the WIDTH / 2
 * (25) right initial distance from the WIDTH / 2
 * (250) distance from the mid of the screen and the tablet y
 */

static void	draw_minimap(t_data *data, t_minimap m, size_t i, size_t d)
{
	while (data->map[i])
	{
		while (data->map[i][d])
		{
			if (m.p.x >= m.s.x && m.p.x < m.e.x
				&& m.p.y >= m.s.y && m.p.y < m.e.y)
			{
				if (data->map[i][d] == '2')
					draw_squareline(data, m, 0xc6c58bAA);
				else if (data->map[i][d] == '3')
					draw_squareline(data, m, 0xc6c58b11);
				else if (data->map[i][d] == '1')
					draw_squareline(data, m, 0xc3cb6eFF);
				else if (data->map[i][d] == 'G')
					draw_squareline(data, m, 0x816e1eFF);
			}
			d++;
			m.p.x += m.unit;
		}
		i++;
		m.p.y += m.unit;
		d = 0;
		m.p.x = m.center.x - (data->player->pos.x / UNIT) * m.unit;
	}
}

static t_minimap	init_data(t_data *data)
{
	t_minimap	m;

	m.ratio.x = data->game->width * 181 / 1280;
	m.ratio.y = data->game->height * 181 / 960;
	m.left = data->game->width * 156 / 1280;
	m.right = data->game->width * 25 / 1280;
	m.y_rat = data->game->height * 250 / 960;
	m.unit = m.ratio.x / 15;
	m.s.x = data->game->width / 2 - m.left;
	m.s.y = data->game->height / 2 + m.y_rat;
	m.center.x = m.s.x + m.ratio.x / 2;
	m.center.y = m.s.y + m.ratio.y / 2;
	m.p.x = m.center.x - (data->player->pos.x / UNIT) * m.unit;
	m.p.y = m.center.y - (data->player->pos.y / UNIT) * m.unit;
	m.e.x = data->game->width / 2 + m.right;
	m.e.y = data->game->height / 2 + m.y_rat + m.ratio.y;
	return (m);
}

void	draw_tablet(t_data *data)
{
	t_minimap	m;
	t_fvec		enemy;

	m = init_data(data);
	enemy.x = m.center.x \
	+ (((data->enemy->pos.x - data->player->pos.x) / UNIT) * m.unit);
	enemy.y = m.center.y \
	+ (((data->enemy->pos.y - data->player->pos.y) / UNIT) * m.unit);
	draw_minimap(data, m, 0, 0);
	draw_player(data, m.center, m.unit / 3);
	if (enemy.x >= m.s.x && enemy.x < m.e.x
		&& enemy.y >= m.s.y && enemy.y < m.e.y)
		draw_circle(data, (t_fvec){enemy.x, enemy.y}, m.unit / 3, 0xFF000011);
	draw_sanity_bar(data);
	draw_compass(data);
}
