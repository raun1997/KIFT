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

#include "kift.h"
// put headers in kift.h for final build
void	curl(char *url, char *filename)
{
	CURL *curl;
	FILE *file;

	remove(filename);
	curl = curl_easy_init();
	file = fopen(filename, "ab+");
	if(curl) {
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
	curl(url, filename);
	system("sh parse_ip_info.sh");
}

void get_events(char *token)
{
	//this needs a way for the token to be refreshed every call before it can be used
	//token expires 7200 sec afer being granted, so doesn't really work well.
	char	*prefix;
	char	*url;
	char	*filename;

	prefix = "https://api.intra.42.fr/v2/campus/fremont/cursus/42/"
			"events?access_token="; // 42 API
	url = (char *)malloc(sizeof(strlen(prefix)) + strlen(token) + 1);
	filename = "json/ft_events.json";
	strcpy(url, prefix);
	strcat(url, token);
	curl(url, filename);
	// may need to be freed when used
}

void get_weather(char *coords)
{ 								//call this with the following coords if parsing not implemented yet
	char	*prefix;			// "37.5486260, -122.0591160"
	char	*postfix;			// "94555"
	char	*url;				// "Fremont, us"
	char	*filename;

	prefix = "http://api.openweathermap.org/data/2.5/weather?q=";
	postfix = "&units=imperial&appid=8c1b88f5ffc94dc1c4ce9d94b4520325";
	url = (char *)malloc(sizeof(strlen(prefix) + strlen(coords)
			+ strlen(postfix) + 1)); //replace strlens with libft
	filename = "json/get_weather.json";
	strcpy(url, prefix);
	strcat(url, coords);
	strcat(url, postfix);
	curl(url, filename);
	free(url);
	// gave free error when I tried freeing it before, be careful
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
	curl(url, filename);
}
