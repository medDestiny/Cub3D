/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:49:02 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 16:25:59 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_scene(t_data *data, int state)
{
	t_scene			*scene;
	t_frame			*frames;
	unsigned int	i;

	i = 0;
	scene = &data->game->scene[state];
	frames = scene->frames;
	while (frames)
	{
		frames->img->enabled = 1;
		frames = frames->next;
	}
}
