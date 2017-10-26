/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:37:21 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/20 18:37:22 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/kift.h"
// put headers in kift.h for final build
void	simple_curl(char *url, char *filename)
{
	CURL *curl;
	FILE *file;

	remove(filename);
	curl = curl_easy_init();
	file = fopen(filename, "ab+");
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(file);
	}
}


void ip_info(void)
{
	char	*url;
	char	*filename;

	url = "https://ipinfo.io";
	filename ="json/ip_info.json";
	simple_curl(url, filename);
	parse_json_in(filename, 2);
}

void get_events(char *token)
{
	//this needs a way for the token to be refreshed every call before it can be used
	//token expires 7200 sec afer being granted, so doesn't really work well.
	char	*url;
	char	*filename;

	asprintf(&url, "https://api.intra.42.fr/v2/campus/fremont/cursus/42/"
			"events?access_token=%s", token); // 42 API
	filename = "json/ft_events.json";
	simple_curl(url, filename);
	parse_json_in(filename, 3);
}

void get_weather(char *coords)
{ 								//call this with the following coords if parsing not implemented yet
								// "37.5486260, -122.0591160"
								// "94555"
	char	*url;				// "Fremont, us"
	char	*filename;

	filename = "json/get_weather.json";
	asprintf(&url, "http://api.openweathermap.org/data/2.5/weather?q=%s"
		"&units=imperial&appid=8c1b88f5ffc94dc1c4ce9d94b4520325", coords);
	simple_curl(url, filename);
	free(url);
	parse_json_in(filename, 0);
}

void get_traffic(void)
{
	char	*url;
	char	*filename;
	// set to fremont-ish area by default, unless someone can figure out how to
	// set the bounding box coordinates. ip_info function can grab our coordinates
	// but it needs a range of coordinates to function
	url = "https://www.mapquestapi.com/traffic/v2/incidents?&out"
			"Format=json&boundingBox=37.73325402695063%2C-121.5963"
			"363647461%2C37.36688292232763%2C-122.3653793334961&key"
			"=FB5ba01IvuP1ZdqzhOqABgzNTGwW482A";
	filename = "json/get_traffic.json";
	simple_curl(url, filename);
	parse_json_in(filename, 1);
}
