/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:49:08 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 18:29:49 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_menu_scene(t_data *data)
{
	t_scene	*scene;

	scene = &data->game->scene[MENU];
	scene->img_max = MENU_IMG_MAX;
	scene->img_index = 0;
	scene->time = 0;
	scene->frames = NULL;
	frame_add(data, MENU, "assets/scenes/menu.png");
}
