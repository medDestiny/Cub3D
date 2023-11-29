/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:41:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 15:04:48 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_win_scene(t_data *data)
{
	t_scene	*scene;

	scene = &data->game->scene[WIN];
	scene->img_max = WIN_IMG_MAX;
	scene->img_index = 0;
	scene->time = 0;
	scene->frames = NULL;
	//frame_add();
}
