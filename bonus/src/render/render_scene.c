/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:49:02 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 20:36:15 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_scene(t_data *data, int state)
{
	t_scene			*scene;

	scene = &data->game->scene[state];
	if (!scene->curr_frame)
		return ;
	if (scene->curr_frame == scene->frames
		|| mlx_get_time() - scene->time >= scene->frame_time)
	{
		scene->curr_frame->img->enabled = 1;
		scene->curr_frame = scene->curr_frame->next;
		scene->time = mlx_get_time();
	}
}
