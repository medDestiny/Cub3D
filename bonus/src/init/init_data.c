/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:47:16 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/06 12:08:33 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	save_map(t_data *data)
{
	int	y;

	y = 0;
	while (data->map[y])
	{
		data->saved_map[y] = ft_strdup(data->map[y]);
		y++;
	}
}

void	init_astar(t_data *data)
{
	data->astar = (t_astar *)ft_malloc(sizeof(t_astar), data, clean_all);
	data->astar->max = get_max_size(data->map);
	data->astar->grid = init_nodes(data->astar->max, data);
	data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), \
	fvec_to_ivec(data->enemy->pos));
}

void	init_game(t_data *data)
{
	data->game = ft_malloc(sizeof(t_game), data, clean_all);
	data->game->width = WIN_WID;
	data->game->height = WIN_HEI;
	data->game->state = MENU;
	data->game->score = NULL;
	init_win_scene(data);
	init_death_scene(data);
	init_insanity_scene(data);
	init_pause_scene(data);
	init_menu_scene(data);
}

void	init_game_data(t_data *data)
{
	data->hud = mlx_load_png("assets/textures/hud3.png");
	if (!data->hud)
		ft_error(MLX_ERR, data, clean_parsing);
	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	if (!data->mlx)
		ft_error(MLX_ERR, data, clean_parsing);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	if (!data->image)
		ft_error(MLX_ERR, data, clean_all);
	data->zbuffer = (float *)ft_malloc(WIN_WID * sizeof(float), data, \
	clean_all);
	save_map(data);
	init_astar(data);
	init_game(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data, clean_all);
	mlx_set_window_limit(data->mlx, 800, 600, 1920, 1080);
}
