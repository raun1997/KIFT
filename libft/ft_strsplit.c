/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 21:00:01 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 01:01:11 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char delim)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == delim && *str != '\0')
			str++;
		else if (*str != delim && *str != '\0')
		{
			count++;
			while (*str != delim && *str != '\0')
				str++;
		}
	}
	return (count);
}

static char	**split(const char *s, char **arr, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
		{
			arr[i][j] = *s;
			j++;
			s++;
			if (*s == '\0')
				break ;
		}
		i++;
		j = 0;
	}
	return (arr);
}

static char	**allocate(const char *s, char **arr, char c)
{
	int		i;
	int		char_count;
	char	*s_cpy;

	i = 0;
	char_count = 0;
	s_cpy = (char *)s;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			char_count++;
			s++;
			if (*s == c || *s == '\0')
			{
				arr[i] = (char *)malloc(sizeof(char) * (char_count) + 1);
				arr[i++][char_count] = '\0';
				char_count = 0;
			}
		}
	}
	arr = split(s_cpy, arr, c);
	return (arr);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**arr;

	if (!s || !c)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	arr[count_words(s, c)] = NULL;
	arr = allocate(s, arr, c);
	return (arr);
}
