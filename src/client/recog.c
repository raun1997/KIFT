/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recog.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:22:57 by scollet           #+#    #+#             */
/*   Updated: 2017/10/27 15:22:58 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

Globals	globals;

static void	audio_callback(void *userdata, Uint8 *stream, int len)
{
	t_client_connection	*con;
	int32_t				num_samples;
	int					rc;

	con = (t_client_connection*)userdata;
	num_samples = len / 2;
	send(con->sock, &num_samples, sizeof(num_samples), 0);
	rc = send(con->sock, stream, len, 0);
}

void run(char *server_reply, t_client_connection *con)
{
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
	return ;
}

void get_get(SDL_AudioSpec *get, t_client_connection *con)
{
	get->freq = 16000;
	get->format = AUDIO_S16LSB;
	get->channels = 1;
	get->samples = BUF_SIZE / 2;
	get->callback = audio_callback;
	get->userdata = con;
}

void check_SDL()
{
  if (!globals.g_devid_in)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't open an audio device for capture: %s!\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  return ;
}

void		recognize(t_client_connection *con)
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
	get_get(&get, con);
	SDL_zero(globals.g_spec);
	globals.g_devid_in = SDL_OpenAudioDevice(NULL, SDL_TRUE, &get, &globals.g_spec, 0);
  check_SDL();
	SDL_PauseAudioDevice(globals.g_devid_in, SDL_FALSE);
	printf("Sending...\n");
	run(server_reply, con);
	SDL_Log("Shutting down.\n");
	SDL_PauseAudioDevice(globals.g_devid_in, 1);
	SDL_CloseAudioDevice(globals.g_devid_in);
	SDL_Quit();
}
