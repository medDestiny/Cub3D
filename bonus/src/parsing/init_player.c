/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:22:09 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 17:28:13 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	init_player(char *line, int x, int y, t_data *data)
{
	if (data->player == NULL)
	{
		data->player = ft_malloc(sizeof(t_player), data, clean_parsing);
		data->player->angle = get_player_angle(line[x]);
		data->player->speed = 2.5 * UNIT;
		data->player->sanity = SANITY;
		data->player->pos.x = x * UNIT + UNIT / 2;
		data->player->pos.y = y * UNIT + UNIT / 2;
		data->player->dir.x = cos(data->player->angle);
		data->player->dir.y = sin(data->player->angle);
	}
	else
	{
		free(line);
		ft_error(PLAYER_DUP, data, clean_parsing);
	}
}
