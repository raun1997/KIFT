// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include "../../../jsmn/jsmn.h"
#include "kift.h"
// #include <curl/curl.h>
// #include <sys/types.h>
// #include <signal.h>

// typedef struct			s_curl
// {
// 	char				*url;
// 	char				*header;
// 	char				*data;
// 	long				data_size;
// 	FILE				*file;
// 	struct curl_slist	*head;
// 	char				*token;
// 	char				*refresh;
// 	int					time;
// }						t_curl;

static int	jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0)
		return (0);
	return (-1);
}

static void	api_curl(t_curl *vars)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl)
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
		//printf("%s\n%s\n%s\n%p\n", vars->url, vars->header, vars->data, vars->file);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}

static void	file_read(t_parse *p, const char *filename)
{
	int r;
	char buf[BUFSIZ];

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

void	parse_json_tkn(t_curl *v, const char *filename)
{
	t_parse p;
	int i;

	file_read(&p, filename);
	jsmn_init(&p.p);
	p.tok = jsmn_parse(&p.p, p.js, p.bytes, p.t, sizeof(p.t)/sizeof(p.t[0]));
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

void	refresh_token(t_curl *vars, const char *filename)
{
	unsigned int secs;

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

static void	init_curl_vars(t_curl *vars)
{
	char s[256];
	char c;
	int n;

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

pid_t		api_token_grab(const char *filename)
{
	t_curl vars;
	pid_t pid;

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
/* return pid to store in a struct. on shutdown of client, call the following functions */
	// kill(pid, SIGTERM);
	// sleep(5);
	// if (waitpid(pid, NULL, WNOHANG) != pid)
	// 	kill(pid, SIGKILL);
}
