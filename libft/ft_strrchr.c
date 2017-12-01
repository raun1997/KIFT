/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 10:34:53 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:58:21 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char *res;

	res = 0;
	if (*str == c)
		res = (char *)str;
	while (*str++)
		if (*str == c)
			res = (char *)str;
	return (res);
}
