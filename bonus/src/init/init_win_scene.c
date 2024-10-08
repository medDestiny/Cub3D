/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:41:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/05 19:10:55 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_win_scene(t_data *data)
{
	t_scene	*scene;

	scene = &data->game->scene[WIN];
	scene->time = 0;
	scene->frames = NULL;
	scene->frame_time = 2.5;
	frame_add(data, WIN, "assets/scenes/win.png");
	frame_add(data, WIN, "assets/scenes/win2.png");
}
