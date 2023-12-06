/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:19:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/06 11:32:38 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	resume_game(t_data *data)
{
	if (data->game->state == PAUSED)
		data->game->pause_time = mlx_get_time() - data->game->pause_time;
	else
		data->game->time = mlx_get_time();
}

void	check_game_keys(mlx_key_data_t keydata, t_data *data)
{
	if (data->game->state != PLAYING && keydata.key == MLX_KEY_SPACE)
	{
		if (data->game->state == WIN
			|| data->game->state == DEATH
			|| data->game->state == INSANITY)
		{
			reset_game(data);
			data->game->time = mlx_get_time();
		}
		else if (data->game->state == PAUSED
			|| data->game->state == MENU)
			resume_game(data);
		data->game->state = PLAYING;
		disable_game_scenes(data);
	}
	else if (data->game->state == PLAYING && keydata.key == MLX_KEY_P)
	{
		data->game->state = PAUSED;
		data->game->pause_time = mlx_get_time();
	}
}
