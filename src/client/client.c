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

#include <time.h>
#include "kift.h"

Globals			globals;

static void	AudioCallback(void *userdata, Uint8 *stream, int len)
{
	t_client_connection	*con;
	int32_t				num_samples;
	int					rc;

	con = (t_client_connection*)userdata;
	num_samples = len / 2;
	send(con->sock, &num_samples, sizeof(num_samples), 0);
	rc = send(con->sock, stream, len, 0);
}

void				recognize(t_client_connection *con)
{
	const char			*devname;
	SDL_AudioSpec		get;
	char				server_reply[BUF_SIZE * 2];

	devname = NULL;
	memset(server_reply, 0, BUF_SIZE * 2);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
	SDL_zero(get);
	get.freq = 16000;
	get.format = AUDIO_S16LSB;
	get.channels = 1;
	get.samples = BUF_SIZE / 2;
	get.callback = AudioCallback;
	get.userdata = con;
	SDL_zero(globals.g_spec);
	globals.g_devid_in = SDL_OpenAudioDevice(NULL, SDL_TRUE, &get, &globals.g_spec, 0);
	if (!globals.g_devid_in)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't open an audio device for capture: %s!\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	SDL_PauseAudioDevice(globals.g_devid_in, SDL_FALSE);
	printf("Sending...\n");
	while (TRUE)
	{
		memset(server_reply, 0, BUF_SIZE * 2);
		if (recv(con->sock, server_reply, BUF_SIZE * 2, 0) < 0)
		{
			perror("recv failed");
			return ;
		}
		printf("\nServer reply : %s\n", server_reply);
		if (parse_reply(server_reply, globals.g_devid_in) == -1)
			break ;
	}
	SDL_Log("Shutting down.\n");
	SDL_PauseAudioDevice(globals.g_devid_in, 1);
	SDL_CloseAudioDevice(globals.g_devid_in);
	SDL_Quit();
}

void				*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return (&(((struct sockaddr_in6*)sa)->sin6_addr));
}

static int	init_connect(t_client_connection *con)
{
	struct addrinfo	hints;
	struct addrinfo	*servinfo;
	int	sockfd;
	int	rv;
	char	*ip;
	char	s[INET6_ADDRSTRLEN];

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	ip = get_ip_str();
	if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return (1);
	}
	con->p = servinfo;
	while (con->p != NULL)
	{
		if ((sockfd = socket(con->p->ai_family,
			con->p->ai_socktype, con->p->ai_protocol)) == -1)
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
	inet_ntop(con->p->ai_family,
		get_in_addr((struct sockaddr *)con->p->ai_addr), s, sizeof(s));
	printf("client: connecting to %s\n", s);
	freeaddrinfo(servinfo);
	return (0);
}

int					main(int argc, char **argv)
{
	t_client_connection	*con;

	//con->pid = api_token_grab("src/client/cmds/json/42_api_token.json");
	srand(time(NULL));
	system("electron . &");
	if (access("logs.log", F_OK) != -1)
		system("rm logs.log");
	con = malloc(sizeof(t_client_connection));
	if (init_connect(con))
		return (-1);
	printf("Connected\n");
	recognize(con);
	close(con->sock);
	kill(con->pid, SIGTERM);
	sleep(5);
	if (waitpid(con->pid, NULL, WNOHANG) != con->pid)
		kill(con->pid, SIGKILL);
	if (con)
		free(con);
	return (0);
}
