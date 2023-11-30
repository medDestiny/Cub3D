/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:53:48 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/30 15:24:27 by mmisskin         ###   ########.fr       */
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

void	check_player(t_data *data, char *map_line, int y)
{
	int	x;

	x = -1;
	while (map_line[++x])
	{
		if (map_line[x] && (map_line[x] == 'N' || map_line[x] == 'S'
				|| map_line[x] == 'E' || map_line[x] == 'W'))
		{
			if (data->player == NULL)
			{
				data->player = ft_malloc(1 * sizeof(t_player), data);
				data->player->angle = get_player_angle(map_line[x]);
				data->player->speed = 2.5 * UNIT;
				data->player->pos.x = x * UNIT + UNIT / 2;
				data->player->pos.y = y * UNIT + UNIT / 2;
				data->player->dir.x = cos(data->player->angle);
				data->player->dir.y = sin(data->player->angle);
			}
			else
			{
				free(map_line);
				ft_error(PLAYER_DUP, data);
			}
		}
	}
}
