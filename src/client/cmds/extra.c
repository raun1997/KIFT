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

void		parse_json_tkn(t_curl *v, const char *filename)
{
	t_parse	p;
	int		i;

	file_read2(&p, filename);
	jsmn_init(&p.p);
	p.tok = jsmn_parse(&p.p, p.js, p.bytes, p.t, sizeof(p.t) / sizeof(p.t[0]));
	if (p.tok < 0)
		printf("Failed to parse JSON: %d\n", p.tok);
	else if (p.tok == 0 ||
			(p.t[0].type != JSMN_OBJECT && p.t[0].type != JSMN_ARRAY))
		printf("Object or Array expected: %d\n", (i = p.tok));
	i = 0;
	while (++i < p.tok)
	{
		if (jsoneq(p.js, &p.t[i], "access_token") == 0 && i++)
			v->token = strndup(p.js + p.t[i].start, p.t[i].end - p.t[i].start);
		else if (jsoneq(p.js, &p.t[i], "refresh_token") == 0 && i++)
			v->ref = strndup(p.js + p.t[i].start, p.t[i].end - p.t[i].start);
		else if (jsoneq(p.js, &p.t[i], "expires_in") == 0 && i++)
			v->time = atoi(p.js + p.t[i].start);
	}
	if (p.js)
		free(p.js);
}

void		refresh_token(t_curl *vars, const char *filename)
{
	unsigned int	secs;

	while (1)
	{
		secs = (uint)vars->time - ((vars->time > 60) ? 60 : (uint)vars->time);
		while (secs--)
			sleep(1);
		vars->data_size = asprintf(&vars->data, "grant_type=refresh_token&"
			"client_id="
			"69a8a73072a7e218b981b00c9b2a8d07cab196e377d84c6aa964e96be485e2c4&"
			"client_secret="
			"d3617e1efd7d1374b02e78495920ff7640c9fa3b5954f54e2811ab1940dc52cb&"
			"code=%s&"
			"redirect_uri=https://self-aware-battle-robot.herokuapp.com/",
			vars->ref);
		vars->file = fopen(filename, "w");
		api_curl(vars);
		fclose(vars->file);
		vars->time = 7200;
	}
	exit(0);
}

pid_t		api_token_grab(const char *filename)
{
	t_curl	vars;
	pid_t	pid;

	system("open \"https://api.intra.42.fr/oauth/authorize?client_id="
		"69a8a73072a7e218b981b00c9b2a8d07cab196e377d84c6aa964e96be485e2c4&"
		"redirect_uri=https%3A%2F%2Fself-aware-battle-robot.herokuapp.com%2F&"
		"response_type=code\"");
	printf("enter code from redirect (found in url as \"?code={code}\"):\n");
	init_curl_vars(&vars);
	if (!(vars.file = fopen(filename, "w")))
		perror("buttfukcer");
	api_curl(&vars);
	fclose(vars.file);
	parse_json_tkn(&vars, filename);
	pid = fork();
	if (pid == 0)
		refresh_token(&vars, filename);
	return (pid);
}
