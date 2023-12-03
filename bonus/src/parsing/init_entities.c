/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:53:48 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 17:28:16 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fill_goal(t_data *data, int x, int y, char *line)
{
	if (data->goal == NULL)
	{
		data->goal = ft_malloc(sizeof(t_sprite), data, clean_parsing);
		data->goal->state = ACTIVE;
		data->goal->pos.x = x * UNIT + UNIT / 2;
		data->goal->pos.y = y * UNIT + UNIT / 2;
		data->goal->tex_max = 1;
		data->goal->tex_index = 0;
		data->goal->texture = ft_malloc(sizeof(mlx_texture_t *),
				data, clean_parsing);
		data->goal->texture[0] = mlx_load_png("assets/textures/door_exit.png");
		if (data->goal->texture[0] == NULL)
		{
			free(line);
			ft_error(MLX_ERR, data, clean_parsing);
		}
	}
	else
	{
		free(line);
		ft_error(GOAL_DUP, data, clean_parsing);
	}
}

void	check_entities(t_data *data, char *map_line, int y)
{
	int	x;

	x = -1;
	while (map_line[++x])
	{
		if (map_line[x] && (map_line[x] == 'N' || map_line[x] == 'S'
				|| map_line[x] == 'E' || map_line[x] == 'W'))
			init_player(map_line, x, y, data);
		else if (map_line[x] == 'e')
			init_enemy(map_line, x, y, data);
		else if (map_line[x] == 'a')
			fill_sprites(data, x, y, map_line);
		else if (map_line[x] == 'G')
			fill_goal(data, x, y, map_line);
	}
}
