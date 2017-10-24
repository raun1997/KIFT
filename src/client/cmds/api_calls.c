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

int	main(void)
{
	char *url;
	char *url2;
	char *url3;
	char *url4;

	url = "https://ipinfo.io"; // Gathers information about IP (Public IP/City/State/Country/Zip/Lat+long cordinates)
	url2 = "http://api.openweathermap.org/data/2.5/weather?q=Fremont,us&units=imperial&appid=8c1b88f5ffc94dc1c4ce9d94b4520325"; // Weather api
	url3 = "https://www.mapquestapi.com/traffic/v2/incidents?&outFormat=json&boundingBox=37.73786977649298%2C-121.5963363647461%2C37.36197126180853%2C-122.3653793334961&key=FB5ba01IvuP1ZdqzhOqABgzNTGwW482A"; // Mapquest traffic api
	url4 = "https://api.intra.42.fr/v2/campus/fremont/cursus/42/events?access_token=e0740d75277a6e2b4116517f6afbf5652207236bb11da94dc2e0539e21ecb92a"; // 42 API
	curl(url);
	curl(url2);
	curl(url3);
	curl(url4);
	return (0);
}
