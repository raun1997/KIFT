/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:54:40 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/07 16:11:58 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	char	*buffer2;

	if (!s)
		return (NULL);
	if (!(buffer = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	buffer2 = buffer;
	while (len--)
		*buffer++ = s[start++];
	*buffer = '\0';
	return (buffer2);
}
