/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:50:33 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 12:44:39 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;
	unsigned int		i;
	unsigned char		j;

	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	i = 0;
	j = (unsigned char)c;
	while (i < n)
	{
		if ((*cdest++ = *csrc++) == j)
		{
			return (cdest);
		}
		i++;
	}
	return (NULL);
}
