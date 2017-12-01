/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 01:01:02 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/08 18:09:57 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char *destcpy;

	destcpy = dest;
	while (n--)
		if (*src == 0)
			*destcpy++ = 0;
		else
			*destcpy++ = *src++;
	if (ft_strlen(src) >= n)
		*dest = '\0';
	return (dest);
}
