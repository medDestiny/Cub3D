/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:58:05 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 12:02:04 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

size_t	get_map_size(int fd)
{
	size_t	map_size;
	char	*map_line;
	char	*tmp;

	map_size = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		map_line = ft_strtrim(tmp, "\t\n\v\f\r ");
		if (map_line && ft_strlen(map_line) > 0)
			map_size++;
		else if (map_line && !ft_strlen(map_line) && map_size != 0)
		{
			free(tmp);
			free(map_line);
			close(fd);
			return (0);
		}
		free(tmp);
		free(map_line);
	}
	close(fd);
	return (map_size);
}

void	fill_map(int map_fd, char **map)
{
	int		i;
	char	*tmp;
	char	*map_line;

	i = 0;
	while (1)
	{
		tmp = get_next_line(map_fd);
		if (!tmp)
			break ;
		map_line = ft_strtrim(tmp, "\t\n\v\f\r ");
		if (map_line && ft_strlen(map_line))
			map[i++] = map_line;
		else
			free(map_line);
		free(tmp);
	}
	map[i] = NULL;
}

char	**read_map(char *path)
{
	char	**map;
	size_t	map_size;
	int		map_fd;

	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (NULL);
	map_size = get_map_size(map_fd);
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0 || map_size == 0)
		return (NULL);
	map = (char **)malloc((map_size + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	fill_map(map_fd, map);
	return (map);
}
