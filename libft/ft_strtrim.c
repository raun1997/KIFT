/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 19:32:57 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 01:02:00 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*btrim(const char *s)
{
	char	*back;
	char	*s_cpy;
	int		back_count;

	back_count = 0;
	back = (char *)s + ft_strlen(s) - 1;
	while (back > s && (*back == ' ' || *back == ',' ||
			*back == '\n' || *back == '\t'))
	{
		back--;
		back_count++;
	}
	s_cpy = (char *)malloc(sizeof(char) * (ft_strlen(s) - back_count + 1));
	if (!s_cpy)
		return (NULL);
	s_cpy[ft_strlen(s) - back_count] = '\0';
	ft_strncpy(s_cpy, s, ft_strlen(s) - back_count);
	return (s_cpy);
}

static char		*ftrim(const char *s)
{
	const char	*front;

	front = s;
	while (*front == ' ' || *front == ',' || *front == '\n' || *front == '\t')
		front++;
	if (*front == 0)
		return (ft_strdup(front));
	s = front;
	s = btrim(s);
	return ((char *)s);
}

char			*ft_strtrim(const char *s)
{
	const char	*trimmed;

	if (s == 0)
		return (NULL);
	trimmed = ftrim(s);
	return ((char *)trimmed);
}
