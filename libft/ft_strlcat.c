/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:55:18 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:56:24 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	size;
	size_t	dest_size;

	d = dest;
	s = src;
	size = n;
	while (n-- != 0 && *d != '\0')
		d++;
	dest_size = d - dest;
	n = size - dest_size;
	if (n == 0)
		return (dest_size + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (dest_size + (s - src));
}
