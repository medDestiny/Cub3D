/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/09/10 18:39:59 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"

int	main()
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(500, 500, "test", true);
	image = mlx_new_image(mlx, 128, 128);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
}
