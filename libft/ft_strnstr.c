/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 12:01:42 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:57:48 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	char	*st;
	char	*su;
	int		len;

	if (*sub == 0)
		return ((char *)str);
	while (*str && n)
	{
		if (*str == *sub)
		{
			st = (char *)str;
			su = (char *)sub;
			len = n;
			while (*st && *su && *st == *su && len--)
			{
				st++;
				su++;
			}
			if (!*su)
				return ((char *)str);
		}
		str++;
		n--;
	}
	return (NULL);
}
