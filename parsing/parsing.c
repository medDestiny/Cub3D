/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:50:07 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/06 00:02:05 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	open_file(char *str)
{
	if (open(str, O_RDONLY) == -1)
	{
		ft_putstr_fd("Error : file dosent exist or permisions not set !\n", 2);
		return (-1);
	}
	return (0);
}

int	check_file(char *str)
{
	char	*exten;
	int		i;
	int		d;

	exten = ".cub";
	i = ft_strlen(str);
	d = ft_strlen(exten);
	if (i < 4)
		return (-1);
	while (i > 0 && d > 0)
	{
		if (exten[d] == str[i])
		{
			i--;
			d--;
		}
		else
		{
			ft_putstr_fd("Error : map extension must be .cub !\n", 2);
			return (-1);
		}
	}
	return (0);		
}

void	parser(char **av, int ac, t_data *data)
{
	int	map_fd;

	map_fd = 0;
	if (ac != 2)
	{
		ft_putstr_fd("Error : enter a valid map !\n", 2);
		exit(-1);
	}
	map_fd = open_file(av[1]);
	if (check_file(av[1]) == -1 || map_fd == -1)
		exit(-1);
		(void)data;
	// if (readmap(map_fd, &data) == -1)
	// 	exit(-1);
}


// size_t	get_map_size_(int fd)
// {
// 	size_t	map_size;
// 	char	*map_line;
// 	char	*tmp;

// 	map_size = 0;
// 	while (1)
// 	{
// 		tmp = get_next_line(fd);
// 		if (!tmp)
// 			break ;
// 		map_line = ft_strtrim(tmp, "");
// 		if (map_line && ft_strlen(map_line) > 0)
// 			map_size++;
// 		else if (map_line && !ft_strlen(map_line) && map_size != 0)
// 		{
// 			free(tmp);
// 			free(map_line);
// 			close(fd);
// 			return (0);
// 		}
// 		free(tmp);
// 		free(map_line);
// 	}
// 	close(fd);
// 	return (map_size);
// }

// void	fill_map_(int map_fd, char **map)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*map_line;

// 	i = 0;
// 	while (1)
// 	{
// 		tmp = get_next_line(map_fd);
// 		if (!tmp)
// 			break ;
// 		map_line = ft_strtrim(tmp, "");
// 		if (map_line && ft_strlen(map_line))
// 			map[i++] = map_line;
// 		else
// 			free(map_line);
// 		free(tmp);
// 	}
// 	map[i] = NULL;
// }

// char	**read_map_(char *path)
// {
// 	char	**map;
// 	size_t	map_size;
// 	int		map_fd;

// 	map_fd = open(path, O_RDONLY);
// 	if (map_fd < 0)
// 		return (NULL);
// 	map_size = get_map_size_(map_fd);
// 	map_fd = open(path, O_RDONLY);
// 	if (map_fd < 0 || map_size == 0)
// 		return (NULL);
// 	map = (char **)malloc((map_size + 1) * sizeof(char *));
// 	if (!map)
// 		return (NULL);
// 	// fill_map(map_fd, map);
// 	return (map);
// }