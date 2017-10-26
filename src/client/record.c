/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:11 by scollet           #+#    #+#             */
/*   Updated: 2017/10/07 14:04:41 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

// SDL_AudioSpec			g_spec;
// SDL_AudioDeviceID		g_devid_in = 0;

/* TODO : initialize this shit */

int			parse_reply(t_audio_var *audio)
{
	SDL_PauseAudioDevice(audio->devid_in, SDL_TRUE);
	/* Take str replies */
	//printf("%s\n", strtok (hyp, " "));
	if (strstr(audio->serv_rep, "YOU")) system("say \"I am SABRE\"");
	else if (strstr(audio->serv_rep, "I AM")) system("say \"Nice to meet you\"");
	else if (strstr(audio->serv_rep, "HELLO")) system("say \"Hello\"");
	if (!strcmp(audio->serv_rep, "SHUTDOWN")){system("say \"Goodbye\""); return(-1);}

	SDL_PauseAudioDevice(audio->devid_in, SDL_FALSE);
	return (0);
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

void		init_sdl_var(SDL_AudioSpec *wanted, t_client_connection *con)
{
	SDL_zero(*wanted);
	wanted->freq = 16000;
	wanted->format = AUDIO_S16LSB;
	wanted->channels = 1;
	wanted->samples = BUF_SIZE / 2;
	wanted->callback = AudioCallback;
	wanted->userdata = con;
}

void		get_audio(t_client_connection *con, t_audio_var *audio)
{
	while (42)
	{
		memset(audio->serv_rep, 0, BUF_SIZE * 2);
		if (recv(con->sock, audio->serv_rep, BUF_SIZE * 2, 0) < 0)
		{
			perror("recv failed");
			return ;
		}
		printf("\nServer reply : %s\n", audio->serv_rep);
		if (parse_reply(audio) == -1)
			return ;
	}
}

void		recognize(t_client_connection *con)
{
	t_audio_var		audio;
	SDL_AudioSpec	wanted;

	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
	init_sdl_var(&wanted, con);
	SDL_zero(audio.spec);
	audio.devid_in = SDL_OpenAudioDevice(NULL, SDL_TRUE, &wanted, &audio.spec, 0);
	printf("devid_in (%d)\n", audio.devid_in);
	if (!audio.devid_in)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't open an audio device for capture: %s!\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	SDL_PauseAudioDevice(audio.devid_in, 0);
	printf("Sending...\n");
	get_audio(con, &audio);
	SDL_Log("Shutting down.\n");
	SDL_PauseAudioDevice(audio.devid_in, 1);
	SDL_CloseAudioDevice(audio.devid_in);
	SDL_Quit();
}
