/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:30:48 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/08 18:06:25 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *sub)
{
	char *st;
	char *su;

	if (*sub == 0)
		return ((char *)str);
	while (*str)
	{
		st = (char *)str;
		su = (char *)sub;
		while (*str && *su && *str == *su)
		{
			str++;
			su++;
		}
		if (!*su)
			return (st);
		str = st + 1;
	}
	return (NULL);
}
