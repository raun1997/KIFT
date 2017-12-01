/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 21:42:20 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:55:27 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		size;
	char	*dest;
	char	*offset;

	size = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return ((char *)NULL);
	offset = dest;
	while (*src)
	{
		*offset = *src;
		offset++;
		src++;
	}
	*offset = '\0';
	return (dest);
}
