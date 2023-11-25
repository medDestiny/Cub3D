/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/25 16:08:38 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_items(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i] != NULL)
			mlx_delete_texture(data->textures[i]);
		i++;
	}
	if (data->map != NULL)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void	ft_error_help(int err_code)
{
	if (err_code == FLOOR_INV)
		ft_putendl_fd("Floor colors are invalid!", 2);
	else if (err_code == CIELING_INV)
		ft_putendl_fd("Cieling colors are invalid!", 2);
	else if (err_code == INV_INPUT)
		ft_putendl_fd("unrecognized map input!", 2);
	else if (err_code == DUP_COLOR)
		ft_putendl_fd("Duplicated Colors !", 2);
	else if (err_code == COLOR_RANGE)
		ft_putendl_fd("Color range must be from 0 to 255\n", 2);
	else if (err_code == MAP_INV)
		ft_putendl_fd("Map is invalid !", 2);
	else if (err_code == MALLOC_ERR)
		ft_putendl_fd("Malloc failed !", 2);
	else if (err_code == PLAYER_DUP)
		ft_putendl_fd("Player is duplicated !", 2);
	else if (err_code == ARG_ERR)
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
	else if (err_code == MLX_ERR)
		ft_putendl_fd(mlx_strerror(mlx_errno), 2);
}

void	ft_error(int err_code, t_data *data)
{
	ft_putendl_fd("Error", 2);
	if (err_code == OPEN_ERR)
		ft_putendl_fd("file dosent exist or permisions not set !", 2);
	else if (err_code == EXT_ERR)
		ft_putendl_fd("map extension must be .cub !", 2);
	else if (err_code == MAP_EMPTY)
		ft_putendl_fd("map file is empty !", 2);
	else if (err_code == DUP_CORD)
		ft_putendl_fd("coordinates are duplicated!", 2);
	else if (err_code == INVA_CORD)
		ft_putendl_fd("coordinate is invalid !", 2);
	else if (err_code == TEX_LOAD_ERR)
		ft_putendl_fd("texture cannot be loaded !", 2);
	else if (err_code == MAP_EXIST)
		ft_putendl_fd("Enter a .cub file !", 2);
	else if (err_code == CORD_MIS)
		ft_putendl_fd("coordinates are incomplete!", 2);
	else
		ft_error_help(err_code);
	if (data != NULL)
		free_items(data);
	exit(err_code);
}
