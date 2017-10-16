/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:37:27 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:51:23 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)dest;
	if (csrc == cdest)
		return (dest);
	if (csrc < cdest)
	{
		csrc = csrc + n - 1;
		cdest = cdest + n - 1;
		while (n--)
			*cdest-- = *csrc--;
	}
	else
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	return (dest);
}
