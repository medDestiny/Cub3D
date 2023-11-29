/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:56:18 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 16:19:48 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fill_frame_node(t_frame *frame, char const *path, t_data *data)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (!tex)
		ft_error(MLX_ERR, data, clean_all);
	frame->img = mlx_texture_to_image(data->mlx, tex);
	mlx_delete_texture(tex);
	if (!frame->img)
		ft_error(MLX_ERR, data, clean_all);
	frame->img->enabled = 0;
	if (mlx_image_to_window(data->mlx, frame->img, 0, 0) == -1)
		ft_error(MLX_ERR, data, clean_all);
	frame->next = NULL;
}

void	frame_add(t_frame **flist, char const *path, t_data *data)
{
	t_frame	*tmp;

	tmp = *flist;
	if (!tmp)
	{
		*flist = ft_malloc(sizeof(t_frame), data, clean_all);
		tmp = *flist;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ft_malloc(sizeof(t_frame), data, clean_all);
		tmp = tmp->next;
	}
	fill_frame_node(tmp, path, data);
}
