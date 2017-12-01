/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:56:05 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/08 18:12:43 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *c1;
	unsigned char *c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while ((*c1 != 0 || *c2 != 0) && (n-- > 0))
	{
		if (*c1 < *c2 || *c1 > *c2)
			return (*c1 - *c2);
		else
		{
			c1++;
			c2++;
		}
	}
	return (0);
}
