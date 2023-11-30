/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:58:37 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/30 11:58:42 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//		 frees the line read by get_next_line and the splitted string used
void	free_content(char *str, char **splitted_str, char *trimmed)
{
	int	i;

	i = 0;
	free (str);
	free (trimmed);
	while (splitted_str[i])
	{
		free(splitted_str[i]);
		i++;
	}
	free (splitted_str);
}
