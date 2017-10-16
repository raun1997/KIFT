/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 15:35:27 by etregoni          #+#    #+#             */
/*   Updated: 2017/03/09 22:05:25 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *res;

	res = (t_list*)malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = malloc(content_size);
	res->content_size = (size_t)malloc(content_size);
	res->next = (struct s_list *)malloc(sizeof(t_list));
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
		res->next = NULL;
		return (res);
	}
	res->content = ft_memmove(res->content, content, content_size);
	res->content_size = content_size;
	res->next = NULL;
	return (res);
}
