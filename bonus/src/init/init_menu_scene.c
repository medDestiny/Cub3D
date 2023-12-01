/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:49:08 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/01 18:09:19 by mmisskin         ###   ########.fr       */
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
	scene->frame_time = 0.15;
	//frame_add(data, MENU, "assets/menu/ezgif-frame-001.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-002.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-003.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-004.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-005.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-006.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-007.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-008.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-009.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-010.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-011.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-012.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-013.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-014.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-015.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-016.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-017.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-018.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-019.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-020.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-021.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-022.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-023.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-024.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-025.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-026.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-027.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-028.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-029.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-030.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-031.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-032.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-033.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-034.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-035.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-036.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-037.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-038.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-039.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-040.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-041.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-042.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-043.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-044.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-045.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-046.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-047.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-048.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-049.png");
	//frame_add(data, MENU, "assets/menu/ezgif-frame-050.png");
	frame_add(data, MENU, "assets/scenes/menu.png");
}
