/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:37:21 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/27 16:41:45 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	simple_curl(char *url, char *filename)
{
	FILE	*file;
	CURL	*curl;

	remove(filename);
	curl = curl_easy_init();
	file = fopen(filename, "ab+");
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(file);
	}
}

void	ip_info(void)
{
	char	*url;
	char	*filename;

	url = "https://ipinfo.io";
	filename = "src/clients/cmds/json/ip_info.json";
	simple_curl(url, filename);
	parse_json_in(filename, 2);
}

void	get_events(const char *tokfile)
{
	char	*url;
	char	*filename;
	t_curl	vars;

	parse_json_tkn(&vars, tokfile);
	asprintf(&url, "https://api.intra.42.fr/v2/campus/fremont/cursus/42/"
			"events?access_token=%s", vars.token);
	filename = "src/clients/cmds/json/ft_events.json";
	simple_curl(url, filename);
	parse_json_in(filename, 3);
}

void	get_weather(char *coords)
{
	char	*url;
	char	*filename;

	filename = "src/client/cmds/json/get_weather.json";
	asprintf(&url, "http://api.openweathermap.org/data/2.5/weather?q=%s"
		"&units=imperial&appid=8c1b88f5ffc94dc1c4ce9d94b4520325", coords);
	simple_curl(url, filename);
	free(url);
	parse_json_in(filename, 0);
}

void	get_traffic(void)
{
	char	*url;
	char	*filename;

	url = "https://www.mapquestapi.com/traffic/v2/incidents?&out"
			"Format=json&boundingBox=37.73325402695063%2C-121.5963"
			"363647461%2C37.36688292232763%2C-122.3653793334961&key"
			"=FB5ba01IvuP1ZdqzhOqABgzNTGwW482A";
	filename = "src/client/cmds/json/get_traffic.json";
	simple_curl(url, filename);
	parse_json_in(filename, 1);
}
