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

const char *g_month[12] =
{
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"
};

void		(*func[4])(t_parse*) =
{
	parse_weather,
	parse_traffic,
	parse_location,
	parse_events
};

char		*apidate_to_str(char *date)
{
	char	*vars[4];
	int		i;
	int		time_vars[3];

	i = -1;
	while (++i < 3)
	{
		vars[i] = i == 1 ? (char*)g_month[atoi(date) - 1] : date;
		while (*date >= '0' && *date <= '9')
			date++;
		*date = '\0';
		date++;
	}
	time_vars[0] = atoi(date);
	time_vars[1] = atoi(date + 3);
	time_vars[2] = time_vars[0] < 12;
	time_vars[0] = time_vars[0] % 12 + (!(time_vars[0] % 12) ? 12 : 0);
	if (time_vars[1])
		asprintf(&vars[3], "%s %s, %s at %d:%d %s", vars[1], vars[2], vars[0],
				time_vars[0], time_vars[1], (time_vars[0] < 12) ? "am" : "pm");
	else
		asprintf(&vars[3], "%s %s, %s at %d %s", vars[1], vars[2], vars[0],
				time_vars[0], time_vars[2] ? "a.m." : "p.m.");
	return (vars[3]);
}

int			event_get_vars(t_parse *p, int st, char **event)
{
	int		i;
	char	*s[2];

	i = st;
	while (p->t[++i].type != JSMN_OBJECT)
	{
		if (jsoneq(p->js, &p->t[i], "name") == 0 && i++)
			s[0] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "begin_at") == 0 && i++)
			s[1] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
	}
	asprintf(event, "%s on %s", s[0], apidate_to_str(s[1]));
	return (i - st - 1);
}

void		parse_events(t_parse *p)
{
	int		i;
	int		count;
	char	*out;
	char	*s[EVENTNO];

	count = EVENTNO;
	i = 0;
	while (++i < p->tok && --count >= 0)
	{
		if (p->t[i].type == JSMN_OBJECT)
			i += event_get_vars(p, i, &s[count]);
	}
	asprintf(&out, "say -v Vicki \"Here are some events at 42:\n"
					"\t%s;\n\t%s;\n\t%s;\"", s[0], s[1], s[2]);
	system(out);
	printf("%s\n", out);
	i = -1;
	while (++i < EVENTNO)
		free(s[i]);
	free(out);
}

void		parse_traffic(t_parse *p)
{
	int		i;
	char	*out;
	char	*s;

	i = 3;
	s = NULL;
	while (p->t[++i].type != JSMN_OBJECT)
	{
		if (jsoneq(p->js, &p->t[i], "fullDesc") == 0 && i++)
		{
			s = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
			break ;
		}
	}
	asprintf(&out, "say -v Vicki \"%s\"", s);
	system(out);
	printf("%s\n", out);
	free(s);
	free(out);
}

void		parse_location(t_parse *p)
{
	int		i;
	char	*out;
	char	*s[3];

	i = 0;
	while (++i < p->tok)
	{
		if (jsoneq(p->js, &p->t[i], "city") == 0 && i++)
			s[0] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "region") == 0 && i++)
			s[1] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "country") == 0 && i++)
			s[2] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
	}
	asprintf(&out, "say -v Vicki \"We are in %s, %s, %s\"",
			s[0], s[1], s[2]);
	system(out);
	printf("%s\n", out);
	i = -1;
	while (++i < 3)
		free(s[i]);
	free(out);
}

void		parse_weather(t_parse *p)
{
	int		i;
	char	*out;
	char	*s[4];

	i = 0;
	while (++i < p->tok)
	{
		if (jsoneq(p->js, &p->t[i], "description") == 0 && i++)
			s[0] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "temp") == 0 && i++)
			s[1] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "temp_min") == 0 && i++)
			s[2] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
		else if (jsoneq(p->js, &p->t[i], "temp_max") == 0 && i++)
			s[3] = strndup(p->js + p->t[i].start, p->t[i].end - p->t[i].start);
	}
	asprintf(&out, "say -v Vicki \"Today's forecast is %s, with a high of %s \
degrees and a low of %s degrees. It is currently %s degrees.\"",
			s[0], s[3], s[2], s[1]);
	system(out);
	i = -1;
	while (++i < 4)
		free(s[i]);
	free(out);
}

void	file_read(t_parse *p)
{
	int		r;
	char	buf[BUFSIZ + 1];

	p->bytes = 0;
	p->js = malloc(1);
	while ((r = fread(buf, 1, BUFSIZ, p->file)) > 0)
	{
		buf[r] = '\0';
		p->js = realloc(p->js, r + p->bytes + 1);
		strncat(p->js, buf, r);
		p->bytes += r;
	}
}

int			parse_json_in(const char *file, int call)
{
	t_parse p;

	p.file = fopen(file, "r");
	file_read(&p);
	fclose(p.file);
	jsmn_init(&p.p);
	p.tok = jsmn_parse(&p.p, p.js, p.bytes, p.t, sizeof(p.t) / sizeof(p.t[0]));
	if (p.tok < 0)
	{
		perror("JSON");
		return (-1);
	}
	if (p.tok < 1 || (p.t[0].type != JSMN_OBJECT && p.t[0].type != JSMN_ARRAY))
	{
		printf("Object or Array expected\n");
		return (-1);
	}
	func[call](&p);
	free(p.js);
	return (0);
}
