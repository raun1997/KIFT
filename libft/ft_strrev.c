/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 00:58:35 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/15 00:58:36 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*front;
	char	*back;
	char	swap;

	front = str;
	back = str;
	while (*back != 0)
		back++;
	back--;
	while (front < back)
	{
		swap = *front;
		*front++ = *back;
		*back-- = swap;
	}
	return (str);
}
