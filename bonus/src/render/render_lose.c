/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:49:20 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/01 11:33:44 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_death(t_data *data)
{
	puts("YOU LOST");
	render_scene(data, DEATH);
}

void	render_insanity(t_data *data)
{
	puts("YOU WENT INSANE");
	render_scene(data, INSANITY);
}
