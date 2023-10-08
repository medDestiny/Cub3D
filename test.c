/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/04 15:03:10 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

# define UNIT 80
# define GRIDSIZE 8

int	grid[GRIDSIZE][GRIDSIZE] = {{0, 0, 0, 0, 0, 0, 0, 0}, 
				    {0, 0, 1, 1, 1, 0, 0, 0}, 
				    {0, 0, 1, 0, 0, 1, 0, 0}, 
				    {0, 0, 1, 0, 0, 1, 0, 0}, 
				    {0, 0, 1, 0, 0, 1, 0, 0}, 
				    {0, 0, 1, 1, 1, 0, 0, 0}, 
				    {0, 0, 0, 0, 0, 0, 0, 0}, 
				    {0, 0, 0, 0, 0, 0, 0, 0} };

void	draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, int color)
{
	int	i;
	int	dx;
	int	dy;
	int	step;
	float	x_inc;
	float	y_inc;
	float	x_start;
	float	y_start;

	i = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy))
		step = abs(dx);	
	else
		step = abs(dy);
	x_inc = dx / (float)step;
	y_inc = dy / (float)step;
	x_start = x1;
	y_start = y1;
	while (i <= step)
	{
		mlx_put_pixel(image, x_start, y_start, color);
		x_start += x_inc;
		y_start += y_inc;
		i++;
	}
}

void	draw_square(mlx_image_t *image, int x, int y, int size, int outline, int color)
{
	int	i;

	i = 0;
	if (color != -1)
	{
		while (i <= size)
		{
			draw_line(image, x, y + i, x + size, y + i, color);
			i++;
		}
	}
	draw_line(image, x, y, x + size, y, outline);
	draw_line(image, x, y, x, y + size, outline);
	draw_line(image, x + size, y, x + size, y + size, outline);
	draw_line(image, x, y + size, x + size, y + size, outline);
}

void	draw_grid(mlx_image_t *image, int grid[GRIDSIZE][GRIDSIZE])
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i < GRIDSIZE)
	{
		j = 0;
		while (j < GRIDSIZE)
		{
			if (grid[i][j] == 0)
				draw_square(image, x, y, UNIT, 0xFFFFFFFF, -1);
			else
				draw_square(image, x, y, UNIT, 0xECF542FF, 0x0000FFFF);
			x += UNIT + 1;
			j++;
		}
		x = 0;
		y += UNIT + 1;
		i++;
	}
}

void	mouse(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	(void)action;
	(void)mods;
	(void)param;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		printf("Right click\n");
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		printf("Left click\n");
}

int	main()
{
	int		win_size;
	mlx_t		*mlx;
	mlx_image_t	*image;

	win_size = (UNIT + 1) * GRIDSIZE;
	mlx = mlx_init(win_size, win_size, "test", true);
	image = mlx_new_image(mlx, win_size, win_size);
	draw_grid(image, grid);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_mouse_hook(mlx, mouse, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
