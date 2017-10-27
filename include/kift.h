/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:30:50 by scollet           #+#    #+#             */
/*   Updated: 2017/10/04 17:30:51 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KIFT_H
#define KIFT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include "../libft/libft.h"
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include <curl/curl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <signal.h>
//#include "portaudio.h"
// Leaving portaudio out until we have a use for it, build intructions
// depend on use case.
#include "jsmn.h"
#include "audio.h"
#include "SDL.h"

# define AUDIO_PATH "src/client/audio/"
# define BACKLOG 16
# define PORT "4242"
# define NAME "SELF-AWARE-BATTLE-ROBOT"
# define IP "10.112.6.9"
# define MAXDATASIZE 100
# define S_RATE (44100)
# define BUF_SIZE 512
# define EVENTNO 3

typedef struct			s_client_connection
{
	int					sock;
	struct addrinfo		*p;
	pid_t				pid;
}						t_client_connection;

typedef struct			s_connection
{
	int					socket_desc;
	int					client_sock;
	char				client_message[BUF_SIZE];
	struct				sockaddr_in server;
	struct				sockaddr_in client;
}						t_connection;

typedef struct			s_audio_var
{
	SDL_AudioDeviceID	devid_in;
	SDL_AudioSpec		w;
	SDL_AudioSpec		spec;
	char				serv_rep[BUF_SIZE * 2];
}						t_audio_var;

typedef struct			s_curl
{
	char				*url;
	char				*header;
	char				*data;
	long				data_size;
	FILE				*file;
	struct curl_slist	*head;
	char				*token;
	char				*ref;
	int					time;
}						t_curl;

typedef struct	s_parse
{
	char		*js;
	jsmn_parser	p;
	jsmntok_t	t[128];
	int			tok;
	FILE		*file;
	int			bytes;
}				t_parse;

typedef enum
{
	UTT_STATE_WAITING,
	UTT_STATE_LISTENING,
	UTT_STATE_FINISHED,
	UTT_STATE_ERROR,
	UTT_STATE_MAX,
	UTT_STATE_QUIT
} t_utt_states;

void user_name(void);
void user_loc(void);
void check_history(void);

pid_t		api_token_grab(const char *filename);
void	parse_json_tkn(t_curl *vars, const char *filename);

int   					example(char *str);
char					*get_ip_str(void);
void					*get_in_addr(struct sockaddr *sa);
const char				*recognize_from_microphone();
void					ip_info(void);
void					recognize(t_client_connection *con);

void	curl(char *url, char *filename);
void ip_info(void);
void get_events(const char *tokfile);
void get_weather(char *coords);
void get_traffic(void);
int			parse_json_in(const char *file, int call);

void		parse_traffic(t_parse *p);
void		parse_location(t_parse *p);
void		parse_weather(t_parse *p);
void		parse_events(t_parse *p);

#endif
