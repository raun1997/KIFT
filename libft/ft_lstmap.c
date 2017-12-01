/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 00:11:39 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/10 00:49:08 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *elem;

	elem = f(lst);
	new = elem;
	if (!lst || !f)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		elem->next = f(lst);
		elem = elem->next;
	}
	return (new);
}
