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
#include <stdlib.h>
#include "kift.h"

#define CMD_PATH "src/client/cmds/"

SDL_AudioSpec			g_spec;
SDL_AudioDeviceID	g_devid_in = 0;

int			random_num(int min, int max)
{
	int	diff;

	diff = max - min;
	return ((int)(((double)(diff + 1) / RAND_MAX) * rand() + min));
}

int			parse_reply(char *hyp)
{
	int		result;
	char	command[BUF_SIZE];
	char	*com;
	int		random;

	result = 0;
	SDL_PauseAudioDevice(g_devid_in, SDL_TRUE);
	if (strstr(hyp, "WHO") && strstr(hyp, "YOU"))
		system("say \"I am SABRE\"");
	else if (strstr(hyp, "I AM"))
		system("say \"Nice to meet you\"");
	else if (strstr(hyp, "HELLO"))
		system("say \"Hello\"");
	else if (strstr(hyp, "WHAT") && strstr(hyp, "YOU") && strstr(hyp, "ARE"))
		system("say \"I am machine\"");
	else if (strstr(hyp, "WHO") && strstr(hyp, "KING"))
	{
		random = random_num(0, 2);
		if (random == 1)
			system("say \"I... am\"");
		else if (random == 2)
			system("say \"Me\"");
	}
	else if (strstr(hyp, "JOKE") && strstr(hyp, "TELL"))
	{
		random = random_num(0, 3);
		if (random == 0)
			system("say \"A man is washing the car with his son.\
										The son asks,\
										Dad, can’t you just use a sponge?\"");
		if (random == 1)
		{
			system("say \"What’s the stupidest animal in the jungle?\"");
			if (strstr(hyp, "WHAT"))
				system("say \"A polar bear\"");
		}
		if (random == 2)
			system("say \"A limbo champion walks into a bar.\
										They are disqualified\"");
		if (random == 3)
			system("say \"Two goldfish are in a tank.\
										One looks to the other and says,\
										You man the guns while I drive.\"");
		if (random == 4)
			system("say \"\"");
		if (random == 5)
			system("say \"\"");
		if (random == 6)
			system("say \"\"");
		if (random == 7)
			system("say \"\"");
		if (random == 8)
			system("say \"\"");
		if (random == 9)
			system("say \"\"");
	}
	else if (strstr(hyp, "LAUNCH") && strstr(hyp, "NUKES"))
		system("sh src/client/cmds/nukes.sh");
	else if (strstr(hyp, "SEND AN EMAIL"))
	{
		system("say \"Sending mail... \"");
		system("python src/client/cmds/send_email.py");
	}
	else if (strstr(hyp, "DIM") && strstr(hyp, "LIGHTS"))
		system("sh src/client/cmds/brightness.sh less");
	if (!strcmp(hyp, "SHUTDOWN"))
	{
		system("say \"Goodbye\"");
		return (-1);
	}
	SDL_PauseAudioDevice(g_devid_in, SDL_FALSE);
	return (result);
}

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
	while (TRUE)
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

void				*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return (&(((struct sockaddr_in6*)sa)->sin6_addr));
}

static int	init_connect(t_client_connection *con, char *addr)
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

int				main(int argc, char **argv)
{
	t_client_connection	*con;

	srand(time(NULL));
	con = malloc(sizeof(t_client_connection));
	if (init_connect(con, get_ip_str()) < 0)
		return (-1);
	printf("Connected\n");
	recognize(con);
	close(con->sock);
	if (con)
		free(con);
	return (0);
}
