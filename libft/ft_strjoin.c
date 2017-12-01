/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 19:19:13 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/08 19:31:19 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *catstr;

	if (!s1 || !s2)
		return (NULL);
	catstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!catstr)
		return (NULL);
	*catstr = '\0';
	ft_strcat(catstr, s1);
	ft_strcat(catstr, s2);
	return (catstr);
}
