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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
// put headers in kift.h for final build

void	curl(char *url)
{
	CURL *curl;
	CURLcode res;
	int i;

	res = 0;
	curl = curl_easy_init();
	i = 0;
	if(curl) {
    	curl_easy_setopt(curl, CURLOPT_URL, url);
    	res = curl_easy_perform(curl);
    	curl_easy_cleanup(curl);
  	}
	printf("%u\n\n", res);
}


void ip_info(void)
{
	char	*url;

	url = "https://ipinfo.io";
	curl(url);
}

void get_events(char *token)
{
	//this needs a way for the token to be refreshed every call before it can be used
	char	*prefix;
	char	*url;

	prefix = "https://api.intra.42.fr/v2/campus/fremont/cursus/42/"
			"events?access_token="; // 42 API
	url = (char *)malloc(sizeof(strlen(prefix)) + strlen(token) + 1);
	strcpy(url, prefix);
	strcat(url, token);
	curl(url);
	// may need to be freed when used
}

void get_weather(char *coords) { //call this with "Fremont,us if ip_info not parsed yet"
	char	*prefix;
	char	*postfix;
	char	*url;

	prefix = "http://api.openweathermap.org/data/2.5/weather?q=";
	postfix = "&units=imperial&appid=8c1b88f5ffc94dc1c4ce9d94b4520325";
	url = (char *)malloc(sizeof(strlen(prefix) + strlen(coords)
			+ strlen(postfix) + 1)); //replace strlens with libft
	strcpy(url, prefix);
	strcat(url, coords);
	strcat(url, postfix);
	curl(url);
	// may leak memory, it's malloc'd without a free but
	// gave free error when I tried freeing it here
}

void get_traffic(void)
{
	char	*url;

	url = "https://www.mapquestapi.com/traffic/v2/incidents?&out"
			"Format=json&boundingBox=37.73325402695063%2C-121.5963"
			"363647461%2C37.36688292232763%2C-122.3653793334961&key"
			"=FB5ba01IvuP1ZdqzhOqABgzNTGwW482A";
	curl(url);
}
