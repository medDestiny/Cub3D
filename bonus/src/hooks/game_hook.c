/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:19:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/30 15:15:37 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_game_keys(mlx_key_data_t keydata, t_data *data)
{
	if (data->game->state != PLAYING)
	{
		if ((data->game->state == WIN
				|| data->game->state == DEATH
				|| data->game->state == INSANITY)
			&& keydata.key == MLX_KEY_SPACE)
		{
			reset_game(data);
		}
		if (keydata.key == MLX_KEY_SPACE)
		{
			data->game->state = PLAYING;
			disable_game_scenes(data);
		}
		return ;
	}
	else if (data->game->state == PLAYING && keydata.key == MLX_KEY_P)
	{
		data->game->state = PAUSED;
		return ;
	}
}
