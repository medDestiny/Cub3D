/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:22:53 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/24 11:44:35 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	//i = 0;
	//while (i < data->enemy->tex_max) // bonus
	//	mlx_delete_texture(data->enemy->texture[i++]);
	// clean sprite list
}

void	clean_astar(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->astar->max.y)
		free(data->astar->grid[i++]);
	free(data->astar->grid);
	free(data->astar);
}

void	clean_all(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	mlx_delete_image(data->mlx, data->image_p);
	mlx_close_window(data->mlx);
	clean_vec(data->map);
	free(data->player);
	clean_textures(data);
	free(data->zbuffer); //bonus
	clean_astar(data); //bonus
	mlx_terminate(data->mlx);
}

void	*ft_malloc(size_t size, t_data *data)
{
	void	*new;

	new = malloc(size);
	if (!new)
		ft_error(MALLOC_ERR, data);
	return (new);
}
