/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:08:42 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/07 19:22:38 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_atoi_2d(char **s, int w)
{
	int *str;
	int i;

	i = 0;
	str = (int *)malloc(sizeof(int) * (w + 1));
	while (i < w)
	{
		str[i] = ft_atoi(&s[i][0]);
		i++;
	}
	return (str);
}
