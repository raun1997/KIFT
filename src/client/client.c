/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:11 by scollet           #+#    #+#             */
/*   Updated: 2017/10/07 14:04:41 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

/* TODO : initialize this shit */

ps_decoder_t *ps;                  // create pocketsphinx decoder structure
cmd_ln_t *config;                  // create configuration structure
ad_rec_t *ad;                      // create audio recording structure - for use with ALSA functions

int16 adbuf[4096];                 // buffer array to hold audio data
uint8 utt_started, an_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
int32 k;                           // holds the number of frames in the audio buffer

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int 	record(void)
{

  /* TODO : make this more robust than a system call */

  return (system("electron ./."));
}

int main(int argc, char **argv)
{
  int	sockfd, numbytes;
  char	*output;
  struct 	addrinfo hints, *servinfo, *p;
  int 	rv;
  char 	s[INET6_ADDRSTRLEN];
  char	*ip;

  /* Client takes IP address of machine as an argument */

	if (argc == 1)
	{

    /* TODO : drop this shit into a function */

		memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
   	hints.ai_socktype = SOCK_STREAM;
  	ip = get_ip_str();
    if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
		{
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
    }
    p = servinfo;
    while (p != NULL) /* CYCLE THROUGH STUFF */
    {
      if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
      {
        perror("client: socket");
        p = p->ai_next;
        continue;
      }
      if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
      {
        close(sockfd);
        perror("client: connect");
        p = p->ai_next;
        continue;
      }
      break;
    }
    if (p == NULL)
    {
      fprintf(stderr, "client: failed to connect\n");
      return (2);
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);
    freeaddrinfo(servinfo);

    /* TODO : drop this shit into a function */

    while (1)
    {

      /* Internal loop while recording user */
      /* TODO : activate recording function on some input instead of attempting to record continuously */

      if (record() <= 0)
        perror("record: \n");
      if ((numbytes = send(sockfd, "./src/client/audio/test4.wav", MAXDATASIZE - 1, 0)) == -1)
      {
        perror("send");
       	exit(1);
      }
      printf("client: sent file successfully\n");
      close(sockfd);
    }
	}
	else
    perror("usage: ./client <host.ip.address> || ");
  return 0;
}
