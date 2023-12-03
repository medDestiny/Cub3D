/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:14:36 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/02 21:35:41 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	disable_game_scenes(t_data *data)
{
	t_frame	*frames;
	int		i;

	i = 0;
	while (i < 5)
	{
		frames = data->game->scene[i].frames;
		data->game->scene[i].curr_frame = frames;
		while (frames)
		{
			if (frames->img)
				frames->img->enabled = 0;
			frames = frames->next;
		}
		i++;
	}
	if (data->game->score)
		data->game->score->enabled = 0;
}
