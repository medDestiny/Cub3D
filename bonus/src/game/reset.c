/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:23:54 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/28 14:25:47 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	reset_enemy(t_data *data, int x, int y)
{
	data->enemy->pos.x = x * UNIT + UNIT / 2;
	data->enemy->pos.y = y * UNIT + UNIT / 2;
}

void	reset_player_mvm(t_player *p)
{
	p->move.front = 0;
	p->move.back = 0;
	p->move.right = 0;
	p->move.left = 0;
}

void	reset_player(t_data *data, int x, int y)
{
	data->player->pos.x = x * UNIT + UNIT / 2;
	data->player->pos.y = y * UNIT + UNIT / 2;
	data->player->angle = get_player_angle(data->saved_map[y][x]);
	data->player->dir.x = cos(data->player->angle);
	data->player->dir.y = sin(data->player->angle);
	reset_player_mvm(data->player);
	data->player->sanity = SANITY;
}

void	reset_sprites(t_data *data)
{
	t_sp_list	*sp;

	sp = data->sprites;
	while (sp)
	{
		sp->sp->state = ACTIVE;
		sp = sp->next;
	}
}

void	reset_game(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->saved_map[y])
	{
		x = 0;
		while (data->saved_map[y][x])
		{
			if (data->saved_map[y][x] == 'e')
				reset_enemy(data, x, y);
			else if (data->saved_map[y][x] == 'N'
			|| data->saved_map[y][x] == 'S'
			|| data->saved_map[y][x] == 'W'
			|| data->saved_map[y][x] == 'E')
				reset_player(data, x, y);
			if (data->saved_map[y][x] == '3')
				data->map[y][x] = '2';
			else
				data->map[y][x] = data->saved_map[y][x];
			x++;
		}
		y++;
	}
	reset_sprites(data);
}
