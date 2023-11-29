/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:38 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:24:53 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	door_hooks(mlx_key_data_t keydata, t_data *data)
{
	int		distance;
	t_ivec	new_pos;
	t_ivec	player;
	t_ivec	enemy;

	distance = UNIT;
	if (keydata.action == MLX_PRESS)
	{
		player.x = (float)data->player->pos.x / UNIT;
		player.y = (float)data->player->pos.y / UNIT;
		enemy.x = (float)data->enemy->pos.x / UNIT;
		enemy.y = (float)data->enemy->pos.y / UNIT;
		new_pos.x = data->player->pos.x + data->player->dir.x * distance;
		new_pos.y = data->player->pos.y + data->player->dir.y * distance;
		if (data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '2')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '3';
		else if (data->map[player.y][player.x] != '3'
			&& data->map[enemy.y][enemy.x] != '3'
			&& data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '3')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '2';
	}
}
