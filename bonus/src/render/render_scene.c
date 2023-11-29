/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:49:02 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 21:19:24 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_scene(t_data *data, int state)
{
	t_scene			*scene;
	unsigned int	i;

	i = 0;
	scene = &data->game->scene[state];
	if (!scene->curr_frame)
		return ;
	scene->curr_frame->img->enabled = 1;
	if (mlx_get_time() - scene->time >= 0.01)
		scene->curr_frame = scene->curr_frame->next;
	if (!scene->curr_frame)
		scene->curr_frame = scene->frames;
	scene->time = mlx_get_time();
}
