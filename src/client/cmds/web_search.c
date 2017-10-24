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

// change include to kift.h and add other includes to kift.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
// This file has it's own main for the sake of unit testing.
// change the function name to something else when including it for the project
int	main(void)
{
	char *input;
	printf("Enter a string\n");
	input = malloc(100);
	fgets(input, 99, stdin);
	web_search(input);
	return (0);
}
