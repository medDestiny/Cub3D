/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:00:00 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/14 16:39:31 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

char *newline_iter(int map_fd, char *str_read)
{
	while (1)
	{
		if(str_read && str_read[0] == '\n')
		{
			free(str_read);
			str_read = get_next_line(map_fd);
		}
		else
			break;
	} 
	return (str_read);
}

// frees the line read by get_next_line and the splitted string used

void	free_content(char *str, char **splitted_str, char *trimmed)
{
	int	i;

	i = 0;
	free(str);
	free (trimmed);
	while (splitted_str[i])
	{
		free(splitted_str[i]);
		i++;
	}
}

size_t	get_map_size(int fd)
{
	size_t	map_size;
	char	*map_line;

	map_size = 1; // map_size inits to 1 since we already read a line while checking elements 
	while (1)
	{
		map_line = get_next_line(fd);
		if (!map_line)
			break ;
		if (map_line && ft_strlen(map_line) > 0)
			map_size++;
		else if (map_line && !ft_strlen(map_line) && map_size != 0)
		{
			free(map_line);
			close(fd);
			return (0);
		}
		free(map_line);
	}
	close(fd);
	return (map_size);
}

int	open_file(char *str, t_data *data)
{
	int	map_fd;

	map_fd = open(str, O_RDONLY);
	if (map_fd == -1)
	{
		ft_error(OPEN_ERR, data);
		exit(OPEN_ERR);
	}
	return (map_fd);
}
