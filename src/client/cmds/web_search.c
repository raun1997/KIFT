/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:08:30 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/21 17:08:32 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

// Possible Optimization : encode special characters because they won't
// translate properly in search terms
// Further explanation here:  https://www.thoughtco.com/encoding-urls-3467463

char *rm_nline(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (str);
}
void web_search(char *terms)
{
	char *search;
	char *url;
	int i;

	search = "open https://www.duckduckgo.com/?q=";
	url = (char *)malloc(strlen(search) + strlen(terms) + 1); //replace strlen with libft function
	i = 0;
	while(terms[i])
	{
		if (terms[i] == ' ')
			terms[i] = '+';
		i++;
	}
	strcpy(url, search); // change to libft functions
	strcat(url, terms); // change to libft functions
	url = rm_nline(url);
	system(url);
	free(url);
}
