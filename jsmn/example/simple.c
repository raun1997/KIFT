#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../jsmn.h"

typedef struct	s_parse
{
	char		*js;
	jsmn_parser	p;
	jsmntok_t	t[1024];
	int			tok;
	FILE		*file;
	int			bytes;
}				t_parse;

void		weather(t_parse *p);

void	(*func[5])(t_parse*) =
{
	weather,
};

static int	jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0)
		return (0);
	return (-1);
}

void		weather(t_parse *p)
{
	int i;
	char *out;
	char *var[4];

	i = 0;
	while (++i < p->tok)
	{
		if (jsoneq(p->js, &p->t[i], "description") == 0 && i++)
			var[0] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "temp") == 0 && i++)
			var[1] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "temp_min") == 0 && i++)
			var[2] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "temp_max") == 0 && i++)
			var[3] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
	}
	asprintf(&out, "say -v Vicki \"Today's forecast is %s, with a high of %s \
degrees and a low of %s degrees. It is currently %s degrees.\"",
			var[0], var[3], var[2], var[1]);
	// system(s);
	printf("%s\n", out);
	i = -1;
	while (++i < 4)
		free(var[i]);
	free(out);
}

static void	file_read(t_parse *p)
{
	int r;
	char buf[BUFSIZ];

	p->bytes = 0;
	while ((r = fread(buf, 1, sizeof(buf), p->file)) > 0)
	{
		p->js = realloc(p->js, r + p->bytes + 1);
		strncpy(p->js + p->bytes, buf, r);
		p->bytes += r;
	}
}

int			main(int ac, char **av)
{
	// int r;
	t_parse p;

	p.file = fopen(av[1], "r");
	file_read(&p);
	jsmn_init(&p.p);
	p.tok = jsmn_parse(&p.p, p.js, p.bytes, p.t, sizeof(p.t)/sizeof(p.t[0]));
	if (p.tok < 0)
	{
		printf("Failed to parse JSON: %d\n", p.tok);
		return (1);
	}
	if (p.tok < 1)
	{
		printf("Object expected\n");
		return (1);
	}
	weather(&p);
	free(p.js);
	fclose(p.file);
	return (0);
}
