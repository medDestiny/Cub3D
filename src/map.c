/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:58:05 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/06 14:52:34 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

// size_t	get_map_size(int fd)
// {
// 	size_t	map_size;
// 	char	*map_line;

// 	map_size = 0;
// 	while (1)
// 	{
// 		puts("stuck");
// 		map_line = get_next_line(fd);
// 		if (!map_line)
// 			break ;
// 		if (map_line && ft_strlen(map_line) > 0)
// 			map_size++;
// 		else if (map_line && !ft_strlen(map_line) && map_size != 0)
// 		{
// 			free(map_line);
// 			close(fd);
// 			return (0);
// 		}
// 		free(map_line);
// 	}
// 	close(fd);
// 	return (map_size);
// }

// void	fill_map(int map_fd, char **map)
// {
// 	int		i;
// 	char	*map_line;

// 	i = 0;
// 	while (1)
// 	{
// 		map_line = get_next_line(map_fd);
// 		if (!map_line)
// 			break ;
// 		if (map_line && ft_strlen(map_line))
// 			map[i++] = map_line;
// 		else
// 			free(map_line);
// 		free(map_line);
// 	}
// 	map[i] = NULL;
// }

// char	**read_map(char *path)
// {
// 	char	**map;
// 	size_t	map_size;
// 	int		map_fd;

// 	map_fd = open(path, O_RDONLY);
// 	if (map_fd < 0)
// 		return (NULL);
// 	map_size = get_map_size(map_fd);
// 	map_fd = open(path, O_RDONLY);
// 	if (map_fd < 0 || map_size == 0)
// 		return (NULL);
// 	map = (char **)malloc((map_size + 1) * sizeof(char *));
// 	if (!map)
// 		return (NULL);
// 	fill_map(map_fd, map);
// 	return (map);
// }



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
		map_line = ft_strtrim(tmp, "");
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
		map_line = ft_strtrim(tmp, "");
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
	close(map_fd);
	return (map);
}