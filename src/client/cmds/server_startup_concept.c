/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:30:46 by snorth            #+#    #+#             */
/*   Updated: 2017/10/27 16:35:50 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int	jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0)
		return (0);
	return (-1);
}

void		api_curl(t_curl *vars)
{
	CURL		*curl;
	CURLcode	res;

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, vars->url);
		if (vars->header)
		{
			vars->head = curl_slist_append(curl, vars->header);
			vars->head = vars->head->next;
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, vars->head);
		}
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, vars->file);
		if (vars->data)
		{
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, vars->data_size);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, vars->data);
		}
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}

void	file_read2(t_parse *p, const char *filename)
{
	int		r;
	char	buf[BUFSIZ];

	p->file = fopen(filename, "r");
	p->bytes = 0;
	p->js = malloc(1);
	while ((r = fread(buf, 1, sizeof(buf), p->file)) > 0)
	{
		p->js = realloc(p->js, r + p->bytes + 1);
		strncpy(p->js + p->bytes, buf, r);
		p->bytes += r;
	}
	fclose(p->file);
}


void	init_curl_vars(t_curl *vars)
{
	char	s[256];
	char	c;
	int		n;

	n = -1;
	while ((c = getchar()) != '\n')
		s[++n] = c;
	s[++n] = '\0';
	vars->url = "https://api.intra.42.fr/oauth/token";
	vars->data_size = asprintf(&vars->data,
		"grant_type=authorization_code&"
		"client_id="
		"69a8a73072a7e218b981b00c9b2a8d07cab196e377d84c6aa964e96be485e2c4&"
		"client_secret="
		"d3617e1efd7d1374b02e78495920ff7640c9fa3b5954f54e2811ab1940dc52cb&"
		"code=%s&"
		"redirect_uri=https://self-aware-battle-robot.herokuapp.com/",
		s);
	vars->header = NULL;
	vars->head = NULL;
}
