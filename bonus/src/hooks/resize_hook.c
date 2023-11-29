/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:17:07 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:17:21 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	resize_all_images(t_data *data)
{
	t_frame		*frames;
	uint32_t	nwid;
	uint32_t	nhei;
	int			i;

	i = 0;
	nwid = data->game->width;
	nhei = data->game->height;
	if (!mlx_resize_image(data->image, nwid, nhei))
		ft_error(MLX_ERR, data, clean_all);
	while (i < 5)
	{
		frames = data->game->scene[i].frames;
		while (frames)
		{
			if (!mlx_resize_image(frames->img, nwid, nhei))
				ft_error(MLX_ERR, data, clean_all);
			frames = frames->next;
		}
		i++;
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->game->width = width;
	data->game->height = height;
	resize_all_images(data);
	free(data->zbuffer);
	data->zbuffer = (float *)ft_malloc(width * sizeof(float), data, clean_all);
}
