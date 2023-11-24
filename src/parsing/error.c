/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/24 15:37:06 by anchaouk         ###   ########.fr       */
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
		ft_putstr_fd("Error\nFloor colors are invalid!\n", 2);
	else if (err_code == CIELING_INV)
		ft_putstr_fd("Error\nCieling colors are invalid!\n", 2);
	else if (err_code == INV_INPUT)
		ft_putstr_fd("Error\nunrecognized map input!\n", 2);
	else if (err_code == DUP_COLOR)
		ft_putstr_fd("Error\nDuplicated Colors !\n", 2);
	else if (err_code == COLOR_RANGE)
		ft_putstr_fd("Error\nColor range must be from 0 to 255\n", 2);
	else if (err_code == MAP_INV)
		ft_putstr_fd("Error\nMap is invalid !\n", 2);
	else if (err_code == MALLOC_ERR)
		ft_putstr_fd("Error\nMalloc failed !\n", 2);
	else if (err_code == PLAYER_DUP)
		ft_putstr_fd("Error\nPlayer is duplicated !\n", 2);
}

void	ft_error(int err_code, t_data *data)
{
	if (err_code == OPEN_ERR)
		ft_putstr_fd("Error\nfile dosent exist or permisions not set !\n", 2);
	else if (err_code == EXT_ERR)
		ft_putstr_fd("Error\nmap extension must be .cub !\n", 2);
	else if (err_code == MAP_EMPTY)
		ft_putstr_fd("Error\nmap file is empty !\n", 2);
	else if (err_code == DUP_CORD)
		ft_putstr_fd("Error\ncoordinates are duplicated!\n", 2);
	else if (err_code == INVA_CORD)
		ft_putstr_fd("Error\ncoordinate is invalid !\n", 2);
	else if (err_code == TEX_LOAD_ERR)
		ft_putstr_fd("Error\ntexture cannot be loaded !\n", 2);
	else if (err_code == MAP_EXIST)
		ft_putstr_fd("Error\nEnter a .cub file !\n", 2);
	else if (err_code == CORD_MIS)
		ft_putstr_fd("Error\ncoordinates are incomplete!\n", 2);
	else
		ft_error_help(err_code);
	if (data != NULL)
		free_items(data);
	exit(err_code);
}
