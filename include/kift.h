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
# define BUF_SIZE 3392
# define EVENTNO 3

typedef struct			s_client_connection
{
	int					sock;
	struct addrinfo		*p;
	struct addrinfo		hints;
	struct addrinfo		*servinfo;
	struct sockaddr		their_addr;
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

typedef struct			s_parse
{
	char				*js;
	jsmn_parser			p;
	jsmntok_t			t[1028];
	int					tok;
	FILE				*file;
	int					bytes;
}						t_parse;

typedef struct Package
{
	int					rv;
	int					score;
	int					read_size;
	int					new_fd;
	const char	*hyp;
}						Package;

typedef enum
{
	UTT_STATE_WAITING = 0,
	UTT_STATE_LISTENING,
	UTT_STATE_FINISHED,
	UTT_STATE_ERROR,
	UTT_STATE_MAX,
	UTT_STATE_QUIT
}						t_utt_states;

typedef struct
{
	SDL_AudioSpec			g_spec;
	SDL_AudioDeviceID	g_devid_in;
}						Globals;

static ps_decoder_t *g_ps;
static cmd_ln_t 	*g_config;
static t_utt_states	g_utt_state = UTT_STATE_WAITING;

void				recognize(t_client_connection *con);
static void			audio_callback(void *userdata, Uint8 *stream, int len);
void 				user_name(void);
void 				user_loc(void);
void 				check_history(void);
pid_t				api_token_grab(const char *filename);
void				parse_json_tkn(t_curl *vars, const char *filename);
static int			read_samples(ps_decoder_t *g_ps, int num_samples, int socket);
int					ready(Package *pack);
int					set(Package *pack);
int					go(Package *pack, int32 num_samples);
int   				example(char *str);
char				*get_ip_str(void);
void				*get_in_addr(struct sockaddr *sa);
const char			*recognize_from_microphone();
void				ip_info(void);
void				recognize(t_client_connection *con);
void				curl(char *url, char *filename);
void				ip_info(void);
void				get_search(char *str);
void				get_events(const char *tokfile);
void				get_weather(char *coords);
void				get_traffic(void);
int					parse_json_in(const char *file, int call);
int					parse_reply(char *hyp, int devid_in);
void				parse_traffic(t_parse *p);
void				parse_location(t_parse *p);
void				parse_weather(t_parse *p);
void				parse_events(t_parse *p);
void				rick(char *hyp, FILE *fp);
void 				smalltalk(char *hyp, FILE *fp);
void 				smalltalk2(char *hyp, FILE *fp);
void 				smalltalk3(char *hyp, FILE *fp);
void 				smalltalk4(char *hyp, FILE *fp);
int					random_num(int min, int max);
void				greetings(char *hyp, FILE *fp);
void				audio(char *hyp, FILE *fp);
void				check(char *hyp, FILE *fp);
void				rick(char *hyp, FILE *fp);
void				jokes(char *hyp, FILE *fp);
void				jokes2(char *hyp, FILE *fp);
void				lights(char *hyp, FILE *fp);
void				lights2(char *hyp, FILE *fp);
void				comms(char *hyp, FILE *fp);
void				actions(char *hyp, FILE *fp);
void				check(char *hyp, FILE *fp);
void				check2(char *hyp, FILE *fp);
void				command_groups(char *hyp, FILE *fp);
void				music_and_stuff(char *hyp, FILE *fp);
pid_t				api_token_grab(const char *filename);
void				refresh_token(t_curl *vars, const char *filename);
void				parse_json_tkn(t_curl *v, const char *filename);
int					jsoneq(const char *json, jsmntok_t *tok, const char *s);
void					api_curl(t_curl *vars);
void					file_read(t_parse *p);
void					init_curl_vars(t_curl *vars);
void					file_read2(t_parse *p, const char *filename);


#endif
