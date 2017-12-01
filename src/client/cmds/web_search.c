/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:08:30 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/27 16:30:27 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	not_found(void)
{
	system("say \"Could not find search term.\"");
}

char	*rm_nline(char *str)
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

void	web_search(char *terms)
{
	char	*search;
	char	*url;
	int		i;

	search = "open https://www.duckduckgo.com/?q=";
	if (!terms)
	{
		not_found();
		return ;
	}
	url = (char *)malloc(strlen(search) + strlen(terms) + 1);
	i = 0;
	while (terms[i])
	{
		if (terms[i] == ' ')
			terms[i] = '+';
		i++;
	}
	strcpy(url, search);
	strcat(url, terms);
	url = rm_nline(url);
	system(url);
	free(url);
}

void	get_search(char *str)
{
	char	*pass;
	char	*four;
	char	*ret;
	int		flag;
	int		i;

	i = -1;
	flag = 0;
	pass = strtok(str, " ");
	while ((pass = strtok(NULL, " ")) != NULL)
	{
		if (!strcmp(pass, "SEARCH"))
		{
			if ((four = strtok(NULL, " ")) != NULL)
				if (strcmp(four, "FOR"))
					flag = 1;
			if ((pass = strtok(NULL, "\0")) != NULL)
				break ;
		}
	}
	if (flag)
	{
		if (pass)
		{
			ret = (char*)malloc(sizeof(char) *
					(strlen(pass) + strlen(four) + 1));
			ret = strcat(ret, four);
			ret = strcat(ret, " ");
			ret = strcat(ret, pass);
		}
		else
			ret = strdup(four);
	}
	if (pass == NULL && !flag)
	{
		not_found();
		return ;
	}
	else if (!flag)
	{
		ret = (char*)malloc(sizeof(char) * strlen(pass));
		ret = strndup(pass, strlen(pass));
	}
	web_search(ret);
	return ;
}
