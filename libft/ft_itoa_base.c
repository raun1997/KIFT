/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 00:44:46 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/15 00:44:48 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert(char *str, int base, int n)
{
	int		i;
	int		rem;
	BOOL	negative;

	i = 0;
	negative = FALSE;
	if (n < 0 && base == 10)
	{
		negative = TRUE;
		n = -n;
	}
	while (n != 0)
	{
		rem = n % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		n /= base;
	}
	if (negative == TRUE)
		str[i++] = '-';
	str[i] = '\0';
	return (str);
}

static char	*imin_or_zero(int n)
{
	char	*str;
	char	*imin;
	char	*zero;

	imin = "-2147483648";
	zero = "0";
	str = (char *)malloc(sizeof(char) * ft_countdigits(n) + 1);
	if (n == -2147483648)
		ft_strcpy(str, imin);
	else
		ft_strcpy(str, zero);
	return (str);
}

char		*ft_itoa_base(int n, char *str, int base)
{
	if (n == -2147483648 || n == 0)
		return (imin_or_zero(n));
	if (!(str = (char *)malloc(sizeof(char) * ft_countdigits(n) + 1)))
		return (NULL);
	str = convert(str, base, n);
	ft_strrev(str);
	return (str);
}
