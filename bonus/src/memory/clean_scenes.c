/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:51:49 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:09:32 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clean_scenes(t_data *data)
{
	t_frame			*frame;
	t_frame			*next;
	unsigned int	i;

	i = 0;
	while (i < 5)
	{
		frame = data->game->scene[i].frames;
		while (frame)
		{
			next = frame->next;
			mlx_delete_image(data->mlx, frame->img);
			free(frame);
			frame = next;
		}
		i++;
	}
	free(data->game);
}
