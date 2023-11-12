/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:53:48 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/12 16:56:04 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	get_player_angle(char p)
{
	float	angle;

	if (p == 'N')
		angle = 3 * M_PI / 2;
	else if (p == 'S')
		angle = M_PI / 2;
	else if (p == 'W')
		angle = M_PI;
	else
		angle = 0;
	return (angle);
}

int	check_player(char c, t_data *data, int x, int y)
{
	if (data->player_flag > 1)
		return (-1);
	if (c && (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
	{
		data->player_flag++;
		if (data->player_flag == 1)
		{
			data->player = malloc(1 * sizeof(t_player));
			data->player->angle = get_player_angle(c);
			data->player->pos.x = x * UNIT + UNIT / 2;
			data->player->pos.y = y * UNIT + UNIT / 2;
			data->player->dir.x =  cos(data->player->angle);
			data->player->dir.y =  sin(data->player->angle);
		}
	}
	return (0);
}
