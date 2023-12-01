/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pause_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:47:57 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/01 11:12:07 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_pause_scene(t_data *data)
{
	t_scene	*scene;

	scene = &data->game->scene[PAUSED];
	scene->img_max = PAUSE_IMG_MAX;
	scene->img_index = 0;
	scene->time = 0;
	scene->frames = NULL;
	scene->frame_time = 0.025;
	frame_add(data, PAUSED, "assets/scenes/paused.png");
}
