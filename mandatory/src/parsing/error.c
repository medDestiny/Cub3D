/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/30 15:19:38 by mmisskin         ###   ########.fr       */
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
	clean_vec(data->map);
}

void	ft_error_help(int err_code)
{
	if (err_code == FLOOR_INV)
		ft_putendl_fd("Floor colors are invalid!", STDERR_FILENO);
	else if (err_code == CIELING_INV)
		ft_putendl_fd("Cieling colors are invalid!", STDERR_FILENO);
	else if (err_code == INV_INPUT)
		ft_putendl_fd("Unrecognized map input!", STDERR_FILENO);
	else if (err_code == DUP_COLOR)
		ft_putendl_fd("Duplicated Colors !", STDERR_FILENO);
	else if (err_code == COLOR_RANGE)
		ft_putendl_fd("Color range must be from 0 to 255", STDERR_FILENO);
	else if (err_code == MAP_INV)
		ft_putendl_fd("Map is invalid !", STDERR_FILENO);
	else if (err_code == MALLOC_ERR)
		ft_putendl_fd("Malloc failed !", STDERR_FILENO);
	else if (err_code == PLAYER_DUP)
		ft_putendl_fd("Player is duplicated !", STDERR_FILENO);
	else if (err_code == ARG_ERR)
		ft_putendl_fd("Usage: ./cub3D <map.cub>", STDERR_FILENO);
	else if (err_code == MLX_ERR)
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
	else if (err_code == PLAYER_MIS)
		ft_putendl_fd("Player is missing from the map !", STDERR_FILENO);
}

void	ft_error(int err_code, t_data *data)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (err_code == OPEN_ERR)
		ft_putendl_fd("File dosent exist or permisions not set !",
			STDERR_FILENO);
	else if (err_code == EXT_ERR)
		ft_putendl_fd("Map extension must be .cub !", STDERR_FILENO);
	else if (err_code == MAP_EMPTY)
		ft_putendl_fd("Map file is empty !", STDERR_FILENO);
	else if (err_code == DUP_CORD)
		ft_putendl_fd("Coordinates are duplicated!", STDERR_FILENO);
	else if (err_code == INVA_CORD)
		ft_putendl_fd("Coordinate is invalid !", STDERR_FILENO);
	else if (err_code == TEX_LOAD_ERR)
		ft_putendl_fd("Texture cannot be loaded !", STDERR_FILENO);
	else if (err_code == MAP_EXIST)
		ft_putendl_fd("Enter a .cub file !", STDERR_FILENO);
	else if (err_code == CORD_MIS)
		ft_putendl_fd("Coordinates are incomplete!", STDERR_FILENO);
	else
		ft_error_help(err_code);
	if (data != NULL)
		free_items(data);
	exit(err_code);
}
