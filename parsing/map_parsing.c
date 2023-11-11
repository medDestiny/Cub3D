/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/11 17:04:10 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_empty(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (0);
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
	if (data->player_flag > 1)
		return (-1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->player_flag++;
	return (0);
}

void	parse_map_fl(char *map_str, t_data *data)
{
	int	i;
	
	i = 0;
	map_str = ft_strtrim(map_str, "\n");
	if (!map_str)
		ft_error(MAP_INV, data);
	map_str = space_iter(map_str);
	if (!map_str)
		ft_error(MAP_INV, data);
	while (map_str[i])
	{
		if (map_str[i] && (map_str[i] == '1' || map_str[i] == ' '))
			i++;
		else
			ft_error(MAP_INV, data);
	}
	free(map_str);
}

void	parse_map_m(char *map_str, t_data *data)
{
	int	i;
	
	i = 0;
	map_str = ft_strtrim(map_str, "\n");
	if (!map_str)
		ft_error(MAP_INV, data);
	map_str = space_iter(map_str);
	if (!map_str)
		ft_error(MAP_INV, data);
	if (map_str[0] != '1' && map_str[i] != ' ')
		ft_error(MAP_INV, data);
	while (map_str[i])
	{
		if (check_player(map_str[i], data) == -1)
		{
			ft_error(MAP_INV, data);
			puts("player err");
		}
		if (map_str[i] == '1' || map_str[i] == ' ' || map_str[i] == '0'
			|| map_str[i] == 'N' || map_str[i] == 'S'|| map_str[i] == 'E' || map_str[i] == 'W')
			i++;
		else
		{
			printf("char = %c\n", map_str[i]);
			ft_error(MAP_INV, data);
		}
	}
	free(map_str);
}

void	init_map(char **map, t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	parse_map(map, data);
	while (map[i])
	{
		if (map[i][0] == '1')
			size++;
		i++;
	}
	data->map = (char **)malloc((size + 1) * sizeof(char *));
	i = 0;
	data->map[size] = NULL;
	while (i < size && map[i])
	{
		data->map[i] = ft_strtrim(map[i], "\n");
		i++;
	}
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
}
