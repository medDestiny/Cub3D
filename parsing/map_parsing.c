/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/10 19:03:40 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_empty(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 
}

char	*space_iter(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == ' ')
		i++;
	return (str);
}

int	check_player(char c, t_data *data)
{
	if (data->player > 1)
		return (-1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->player_flag++;
	return (0);
}

void	parse_map_fl(char *map_str, t_data *data)
{
	int	i;
	
	i = 0;
	while (map_str[i])
	{
		if (map_str[i] == '1' || map_str[i] == ' ')
			i++;
		else
			ft_error(MAP_INV, data);
	}
}

void	parse_map_m(char *map_str, t_data *data)
{
	int	i;
	
	i = 0;
	if (!map_str)
		ft_error(MAP_INV, data);
	map_str = space_iter(map_str);
	if (map_str[0] != '1' && map_str[i] != ' ')
		ft_error(MAP_INV, data);
	while (map_str[i])
	{
		if (check_player(map_str[i], data) == 1)
			ft_error(MAP_INV, data);
		if (map_str[i] == '1' || map_str[i] == ' ')
			i++;
		else
			ft_error(MAP_INV, data);
	}
}

void	init_map(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	
	printf("map size = %d\n", i);
	// while (map[i])
	// {
	// 	if (map[i] && i == 0)
	// 		parse_map_fl(map[i], data);
	// 	else if (map[i] && )
	// }
	// parse_map_fl(map, data);
	// while (1)
	// {
	// 	str_read = get_next_line(map_fd);
	// 	if (!str_read)
	// 		break;
	// 	else if (check_empty(str_read) == -1 || str_read[0] == '\n')
	// 	{
	// 		free(str_read);	
	// 		ft_error(MAP_INV, data);
	// 	}
	// 	free(str_read);
	// }
}