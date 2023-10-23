/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:58:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 12:03:29 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"

size_t	get_map_size(int fd);
void	fill_map(int map_fd, char **map);
char	**read_map(char *path);

#endif
