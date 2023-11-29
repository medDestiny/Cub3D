/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:20:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:30:58 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../../MLX42/include/MLX42/MLX42.h"

# define DEATH_IMG_MAX 1
# define WIN_IMG_MAX 1
# define INSANITY_IMG_MAX 1
# define PAUSE_IMG_MAX 1
# define MENU_IMG_MAX 1

typedef struct s_data	t_data;

typedef struct s_frame
{
	mlx_image_t		*img;
	struct s_frame	*next;
}	t_frame;

typedef struct s_scene
{
	t_frame			*frames;
	double			time;
	unsigned int	img_index;
	unsigned int	img_max;
}	t_scene;

/*
 * Set of functions to init and render a scene
 */

void	init_win_scene(t_data *data);
void	init_death_scene(t_data *data);
void	init_insanity_scene(t_data *data);
void	init_pause_scene(t_data *data);
void	init_menu_scene(t_data *data);

void	frame_add(t_frame **flist, char const *path, t_data *data);

void	render_scene(t_data *data, int state);

#endif
