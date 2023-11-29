/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:09:52 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:10:04 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clean_sprite(t_sprite *sp)
{
	unsigned int	i;

	i = 0;
	while (i < sp->tex_max)
		mlx_delete_texture(sp->texture[i++]);
	free(sp->texture);
	free(sp);
}

void	clean_sprite_list(t_sp_list *sprites)
{
	t_sp_list	*sp;

	while (sprites)
	{
		sp = sprites->next;
		clean_sprite(sprites->sp);
		free(sprites);
		sprites = sp;
	}
}
