/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 20:17:47 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/07 22:42:42 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char p1;
	unsigned char p2;

	while (n > 0)
	{
		p1 = *(unsigned char *)s1;
		p2 = *(unsigned char *)s2;
		if (p1 != p2)
			return (p1 - p2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
