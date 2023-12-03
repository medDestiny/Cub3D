/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:08:16 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 22:51:03 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_enemy_tex(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (data->enemy->texture[i] == NULL)
		{
			free(line);
			ft_error(ENEMY_TEX_ERR, data, clean_parsing);
		}
		i++;
	}
}

static void	init_enemy_textures(t_data *data, char *line)
{
	data->enemy->texture[0] = mlx_load_png("assets/enemy/scp01.png");
	data->enemy->texture[1] = mlx_load_png("assets/enemy/scp02.png");
	data->enemy->texture[2] = mlx_load_png("assets/enemy/scp03.png");
	data->enemy->texture[3] = mlx_load_png("assets/enemy/scp04.png");
	data->enemy->texture[4] = mlx_load_png("assets/enemy/scp05.png");
	data->enemy->texture[5] = mlx_load_png("assets/enemy/scp06.png");
	data->enemy->texture[6] = mlx_load_png("assets/enemy/scp07.png");
	data->enemy->texture[7] = mlx_load_png("assets/enemy/scp08.png");
	data->enemy->texture[8] = mlx_load_png("assets/enemy/scp09.png");
	data->enemy->texture[9] = mlx_load_png("assets/enemy/scp10.png");
	data->enemy->texture[10] = mlx_load_png("assets/enemy/scp11.png");
	data->enemy->texture[11] = mlx_load_png("assets/enemy/scp12.png");
	data->enemy->texture[12] = mlx_load_png("assets/enemy/scp13.png");
	data->enemy->texture[13] = mlx_load_png("assets/enemy/scp14.png");
	data->enemy->texture[14] = mlx_load_png("assets/enemy/scp15.png");
	data->enemy->texture[15] = mlx_load_png("assets/enemy/scp16.png");
	data->enemy->texture[16] = mlx_load_png("assets/enemy/scp17.png");
	check_enemy_tex(data, line);
}

void	init_enemy(char *line, int x, int y, t_data *data)
{
	if (data->enemy == NULL)
	{
		data->enemy = ft_malloc(sizeof(t_sprite), data, clean_parsing);
		data->enemy->state = ACTIVE;
		data->enemy->tex_max = 17;
		data->enemy->tex_index = 0;
		data->enemy->texture = ft_malloc(data->enemy->tex_max
				* sizeof(mlx_texture_t *), data, clean_parsing);
		data->enemy->pos.x = x * UNIT + UNIT / 2;
		data->enemy->pos.y = y * UNIT + UNIT / 2;
		init_enemy_textures(data, line);
	}
	else
	{
		free(line);
		ft_error(ENEMY_DUP, data, clean_parsing);
	}
}
