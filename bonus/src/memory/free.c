/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:22:53 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:10:25 by mmisskin         ###   ########.fr       */
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
	int			i;

	i = 0;
	while (i < 4)
		mlx_delete_texture(data->textures[i++]);
	mlx_delete_texture(data->door);
}

void	clean_astar(t_data *data)
{
	int	i;

	i = 0;
	if (!data->astar)
		return ;
	while (data->astar->grid && i < data->astar->max.y)
		free(data->astar->grid[i++]);
	free(data->astar->grid);
	free(data->astar);
}

void	clean_all(t_data *data)
{
	clean_vec(data->map);
	clean_vec(data->saved_map);
	free(data->player);
	clean_textures(data);
	free(data->zbuffer);
	clean_astar(data);
	clean_sprite_list(data->sprites);
	clean_sprite(data->enemy);
	clean_scenes(data);
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
}

void	*ft_malloc(size_t size, t_data *data, void (clean)(t_data *))
{
	void	*new;

	new = ft_calloc(1, size);
	if (!new)
		ft_error(MALLOC_ERR, data, clean);
	return (new);
}
