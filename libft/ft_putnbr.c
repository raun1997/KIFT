/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:56:18 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:51:56 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_recur(int n)
{
	if (n > 9 || n < -9)
		putnbr_recur(n / 10);
	if (n < 0)
		ft_putchar(-(n % 10) + '0');
	else
		ft_putchar(n % 10 + '0');
}

void		ft_putnbr(int n)
{
	if (n < 0)
		ft_putchar('-');
	putnbr_recur(n);
}
