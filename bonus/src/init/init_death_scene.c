/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_death_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:46:31 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 21:08:58 by mmisskin         ###   ########.fr       */
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
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-001.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-002.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-003.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-004.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-005.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-006.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-007.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-008.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-009.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-010.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-011.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-012.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-013.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-014.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-015.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-016.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-017.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-018.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-019.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-020.png");
	frame_add(data, DEATH, "assets/jumpscare/ezgif-frame-021.png");
	frame_add(data, DEATH, "assets/jumpscare/death.png");
}
