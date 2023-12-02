/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:20:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/02 10:09:42 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct s_data	t_data;

typedef struct s_frame
{
	mlx_image_t		*img;
	struct s_frame	*next;
}	t_frame;

typedef struct s_scene
{
	t_frame			*curr_frame;
	t_frame			*frames;
	float			frame_time;
	double			time;
}	t_scene;

/*
 * Set of functions to init and render a scene
 */

void	init_win_scene(t_data *data);
void	init_death_scene(t_data *data);
void	init_insanity_scene(t_data *data);
void	init_pause_scene(t_data *data);
void	init_menu_scene(t_data *data);

void	frame_add(t_data *data, int scene, char const *path);

void	render_scene(t_data *data, int state);

#endif
