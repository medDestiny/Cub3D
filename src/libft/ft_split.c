/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:11:01 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/05 18:39:09 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	op;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		op = 1;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (op == 1)
			{
				count++;
				op = 0;
			}
		i++;
		}
	}
	return (count);
}

static char	**freeme(char **array, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**elgatto(char const *s, char c, char **array, int start)
{
	int		i;
	int		j;
	int		finish;

	i = -1;
	j = 0;
	finish = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != c && start == -1)
			start = i;
		if ((s[i] != c && finish == -1 && s[i + 1] == c) || s[i + 1] == '\0')
			finish = i + 1;
		if (start != -1 && finish != -1)
		{
			array[j] = ft_substr(s, start, finish - start);
			if (!array[j])
				return (freeme(array, j));
			j++;
			start = -1;
			finish = -1;
		}
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	wordcount;
	char	**res;
	char	**array;
	int		start;

	if (!s)
		return (0);
	wordcount = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (0);
	start = -1;
	res = elgatto(s, c, array, start);
	return (res);
}