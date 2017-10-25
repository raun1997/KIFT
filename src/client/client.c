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

SDL_AudioSpec			g_spec;
SDL_AudioDeviceID		g_devid_in = 0;

/* TODO : initialize this shit */

ps_decoder_t *ps;                  // create pocketsphinx decoder structure
cmd_ln_t *config;                  // create configuration structure
ad_rec_t *ad;                      // create audio recording structure - for use with ALSA functions

int16 adbuf[4096];                 // buffer array to hold audio data
uint8 utt_started, an_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
int32 k;                           // holds the number of frames in the audio buffer

int			parse_reply(char *hyp)
{
	int		result;
	char	command[BUF_SIZE];

	result = 0;
	SDL_PauseAudioDevice(g_devid_in, SDL_TRUE);

	/* Take str replies */
	int points = 1;

	if (!strstr(hyp, "WHO ARE YOU") && points++) system("say \"I am SABRE\"");
	else if (!strstr(hyp, "I AM SAM") || points == 1) system("say \"Nice to meet you\"");
	else if (!strstr(hyp, "HELLO")) system("say \"Hello\"");
	if (!strcmp(hyp, "SHUTDOWN")){system("say \"Goodbye\""); return(-1);}

	SDL_PauseAudioDevice(g_devid_in, SDL_FALSE);
	return (result);
}

static void				AudioCallback(void *userdata, Uint8 *stream, int len)
{
	t_client_connection	*con;
	int32_t				num_samples;
	int					rc;

	con = (t_client_connection*)userdata;
	num_samples = len / 2;
	send(con->sock, &num_samples, sizeof(num_samples), 0);
	rc = send(con->sock, stream, len, 0);
}

void					recognize(t_client_connection *con)
{
	const char			*devname;
	SDL_AudioSpec		wanted;
	char				server_reply[BUF_SIZE * 2];

	devname = NULL;
	memset(server_reply, 0, BUF_SIZE * 2);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
	SDL_zero(wanted);
	wanted.freq = 16000;
	wanted.format = AUDIO_S16LSB;
	wanted.channels = 1;
	wanted.samples = BUF_SIZE / 2;
	wanted.callback = AudioCallback;
	wanted.userdata = con;
	SDL_zero(g_spec);
	g_devid_in = SDL_OpenAudioDevice(NULL, SDL_TRUE, &wanted, &g_spec, 0);
	printf("g_devid_in (%d)\n", g_devid_in);
	if (!g_devid_in)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't open an audio device for capture: %s!\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	SDL_PauseAudioDevice(g_devid_in, SDL_FALSE);
	printf("Sending...\n");
	while (42)
	{
		memset(server_reply, 0, BUF_SIZE * 2);
		if (recv(con->sock, server_reply, BUF_SIZE * 2, 0) < 0)
		{
			perror("recv failed");
			return ;
		}
		printf("\nServer reply : %s\n", server_reply);
		if (parse_reply(server_reply) == -1)
			break ;
	}
	SDL_Log("Shutting down.\n");
	SDL_PauseAudioDevice(g_devid_in, 1);
	SDL_CloseAudioDevice(g_devid_in);
	SDL_Quit();
}

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
  	return &(((struct sockaddr_in*)sa)->sin_addr);
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static int				init_connect(t_client_connection *con, char *addr)
{
	struct addrinfo hints, *servinfo;
	int sockfd;
	char *ip;
	int rv;
	char s[INET6_ADDRSTRLEN];

	hints.ai_family = AF_UNSPEC;
 	hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;
	ip = get_ip_str();
  if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
	{
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }
  con->p = servinfo;

	while (con->p != NULL) /* CYCLE THROUGH STUFF */
  {
    if ((sockfd = socket(con->p->ai_family, con->p->ai_socktype, con->p->ai_protocol)) == -1)
    {
      perror("client: socket");
      con->p = con->p->ai_next;
      continue;
    }
		con->sock = sockfd;
    if (connect(sockfd, con->p->ai_addr, con->p->ai_addrlen) == -1)
    {
      close(sockfd);
      perror("client: connect");
      con->p = con->p->ai_next;
      continue;
    }
    printf("Client socket : %d\n", sockfd);
    break ;
  }
  if (con->p == NULL)
  {
    fprintf(stderr, "client: failed to connect\n");
    return (-1);
  }
  inet_ntop(con->p->ai_family, get_in_addr((struct sockaddr *)con->p->ai_addr), s, sizeof s);
  printf("client: connecting to %s\n", s);
  freeaddrinfo(servinfo);
	return (0);
}

int main(int argc, char **argv)
{
  t_client_connection	*con;

  	con = malloc(sizeof(t_client_connection));
		if (init_connect(con, get_ip_str()) < 0)
  		return (-1);
  	printf("Connected\n");
  	recognize(con);
  	close(con->sock);
		if (con) free(con);
  	return (0);

  // int	sockfd, numbytes;
  // char	*output;
  // struct 	addrinfo hints, *servinfo, *p;
  // int 	rv;
  // char 	s[INET6_ADDRSTRLEN];
  // char	*ip;
  //
  // /* Client takes IP address of machine as an argument */
  //
	// //if (argc == 1)
	// //{
  //
  // /* TODO : drop this shit into a function */
  //
	// memset(&hints, 0, sizeof hints);
  // hints.ai_family = AF_UNSPEC;
 // 	hints.ai_socktype = SOCK_STREAM;
  // hints.ai_protocol = 0;
	// ip = get_ip_str();
  // if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
	// {
  //   fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
  //   return 1;
  // }
  // p = servinfo;
  // while (p != NULL) /* CYCLE THROUGH STUFF */
  // {
  //   if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
  //   {
  //     perror("client: socket");
  //     p = p->ai_next;
  //     continue;
  //   }
  //   if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
  //   {
  //     close(sockfd);
  //     perror("client: connect");
  //     p = p->ai_next;
  //     continue;
  //   }
  //   printf("Client socket : %d\n", sockfd);
  //   break;
  // }
  // if (p == NULL)
  // {
  //   fprintf(stderr, "client: failed to connect\n");
  //   return (2);
  // }
  // inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
  // printf("client: connecting to %s\n", s);
  // freeaddrinfo(servinfo);
  //
  // /* TODO : drop this shit into a function */
  //
  // int u = 1;
  // while (u)
  // {
  //
  //   /* Internal loop while recording user */
  //   /* TODO : activate recording function on some input instead of attempting to record continuously */
  //   /* NOTE : Using external input we can let the user decide when to activate, just not sure how ... */
  //
  //   record();
  //   printf("Finished recording ... \n");
  //   //printf();
  //   if ((numbytes = send(sockfd, "./src/client/audio/test4.wav", MAXDATASIZE - 1, 0)) == -1)
  //   {
  //     perror("send");
  //    	exit(1);
  //   }
  //   printf("number of bytes sent : %d\n", numbytes);
  //   printf("client: sent file successfully\n");
  //   close(sockfd);
  //   u = !u;
  // }
  // return 0;
}
