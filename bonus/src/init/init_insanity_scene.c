/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_insanity_scene.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:47:20 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 18:30:10 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_insanity_scene(t_data *data)
{
	t_scene	*scene;

	scene = &data->game->scene[INSANITY];
	scene->img_max = INSANITY_IMG_MAX;
	scene->img_index = 0;
	scene->time = 0;
	scene->frames = NULL;
	frame_add(data, INSANITY, "assets/scenes/sanity1.png");
	frame_add(data, INSANITY, "assets/scenes/sanity2.png");
	frame_add(data, INSANITY, "assets/scenes/sanity3.png");
	frame_add(data, INSANITY, "assets/scenes/sanity4.png");
	frame_add(data, INSANITY, "assets/scenes/sanity5.png");
}
