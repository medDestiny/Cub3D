/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/08 02:03:46 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	data->game.width = WIN_WID;
	data->game.height = WIN_HEI;
	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	if (!data->mlx)
		ft_error(MLX_ERR, data);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	if (!data->image)
		ft_error(MLX_ERR, data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data);
}

void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_hooks, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_close_hook(data->mlx, close_hook, data);
	mlx_loop_hook(data->mlx, hooks, data);
}

void	mohsine()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	atexit(mohsine);
	parser(av, ac, &data);
	init_data(&data);
	draw_scene(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx);
}
