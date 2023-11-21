/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/21 13:55:49 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_items(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(data->textures[i]);
		i++;
	}
}

void	ft_error(int err_code, t_data *data)
{
	if (err_code == OPEN_ERR)
		ft_putstr_fd("Error : file dosent exist or permisions not set !\n", 2);
	else if (err_code == EXT_ERR)
		ft_putstr_fd("Error : map extension must be .cub !\n", 2);
	else if (err_code == MAP_EMPTY)
		ft_putstr_fd("Error : map file is empty !\n", 2);
	else if (err_code == DUP_CORD)
		ft_putstr_fd("Error : coordinates are duplicated!\n", 2);
	else if (err_code == INVA_CORD)
		ft_putstr_fd("Error : coordinate is invalid !\n", 2);
	else if (err_code == TEX_LOAD_ERR)
		ft_putstr_fd("Error : texture cannot be loaded !\n", 2);
	else if (err_code == MAP_EXIST)
		ft_putstr_fd("Error : Enter a .cub file !\n", 2);
	else if (err_code == CORD_MIS)
		ft_putstr_fd("Error : coordinates are incomplete!\n", 2);
	else if (err_code == FLOOR_INV)
		ft_putstr_fd("Error : Floor colors are invalid!\n", 2);
	else if (err_code == CIELING_INV)
		ft_putstr_fd("Error : Cieling colors are invalid!\n", 2);
	else if (err_code == INV_INPUT)
		ft_putstr_fd("Error : unrecognized map input!\n", 2);
	else if (err_code == DUP_COLOR)
		ft_putstr_fd("Error : Only two colors are allowed \nF\nC\n", 2);
	else if (err_code == COLOR_RANGE)
		ft_putstr_fd("Error : Color range must be from 0 to 255\nF\nC\n", 2);
	else if (err_code == MAP_INV)
		ft_putstr_fd("Error : Map is invalid !\n", 2);
	else if (err_code == MALLOC_ERR)
		ft_putstr_fd("Error : Malloc failed !\n", 2);
	if (data != NULL)
		free_items(data);
	exit(err_code);
}
