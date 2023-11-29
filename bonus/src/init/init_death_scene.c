/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_death_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:46:31 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 15:55:16 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_death_scene(t_data *data)
{
	t_scene	*scene;

	scene = &data->game->scene[DEATH];
	scene->img_max = DEATH_IMG_MAX;
	scene->img_index = 0;
	scene->time = 0;
	scene->frames = NULL;
	//frame_add(&scene->frames, "", data);
	//frame_add(&scene->frames, "", data);
	//frame_add(&scene->frames, "", data);
	//frame_add(&scene->frames, "", data);
}
