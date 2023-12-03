/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:19:18 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 17:28:00 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_sp_list	*add_node(t_data *data, char *line)
{
	t_sp_list	*ptr;

	ptr = ft_malloc(sizeof(t_sp_list), data, clean_parsing);
	ptr->sp = ft_malloc(sizeof(t_sprite), data, clean_parsing);
	ptr->sp->state = ACTIVE;
	ptr->sp->tex_max = 1;
	ptr->sp->tex_index = 0;
	ptr->sp->texture = ft_malloc(sizeof(mlx_texture_t *), data, clean_parsing);
	ptr->sp->texture[0] = mlx_load_png("assets/textures/almondw.png");
	if (ptr->sp->texture[0] == NULL)
	{
		free(line);
		ft_error(MLX_ERR, data, clean_parsing);
	}
	ptr->next = NULL;
	return (ptr);
}

void	fill_sprites(t_data *data, int x, int y, char *line)
{
	t_sp_list	*tmp;

	tmp = data->sprites;
	if (data->sprites == NULL)
	{
		tmp = add_node(data, line);
		data->sprites = tmp;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(data, line);
		tmp = tmp->next;
	}
	tmp->sp->pos.x = x * UNIT + UNIT / 2;
	tmp->sp->pos.y = y * UNIT + UNIT / 2;
	tmp->next = NULL;
}
