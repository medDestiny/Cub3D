/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:22:53 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/26 11:29:23 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clean_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}

void	clean_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_delete_texture(data->textures[i++]);
}

void	clean_all(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	mlx_close_window(data->mlx);
	clean_vec(data->map);
	free(data->player);
	clean_textures(data);
	mlx_terminate(data->mlx);
}

void	*ft_malloc(size_t size, t_data *data)
{
	void	*new;

	new = ft_calloc(1, size);
	if (!new)
		ft_error(MALLOC_ERR, data);
	return (new);
}
