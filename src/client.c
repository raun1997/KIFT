/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:11 by scollet           #+#    #+#             */
/*   Updated: 2017/10/04 16:25:13 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/kift.h"
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>

# define NAME "SELF-AWARE-BATTLE-ROBOT"
// get sockaddr, IPv4 or IPv6:
//const char *recognize_from_microphone();

// TODO : initialize this shit

ps_decoder_t *ps;                  // create pocketsphinx decoder structure
cmd_ln_t *config;                  // create configuration structure
ad_rec_t *ad;                      // create audio recording structure - for use with ALSA functions

int16 adbuf[4096];                 // buffer array to hold audio data
uint8 utt_started, in_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
int32 k;                           // holds the number of frames in the audio buffer
//char const *decoded_speech;

config = cmd_ln_init(NULL, ps_args(), TRUE,                   // Load the configuration structure - ps_args() passes the default values
"-hmm", "/usr/local/share/pocketsphinx/model/en-us/en-us",  // path to the standard english language model
"-lm", "custom.lm",                                         // custom language model (file must be present)
"-dict", "custom.dic",                                      // custom dictionary (file must be present)
"-logfn", "/dev/null",                                      // suppress log info from being sent to screen
 NULL);

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

const char *recognize_from_microphone()
{
	ad_start_rec(ad);                                // start recording
	ps_start_utt(ps);                                // mark the start of the utterance
	utt_started = FALSE;                             // clear the utt_started flag
  char const *hyp;

	while (1)
	{
    k = ad_read(ad, adbuf, 4096);                // capture the number of frames in the audio buffer
    ps_process_raw(ps, adbuf, k, FALSE, FALSE);  // send the audio buffer to the pocketsphinx decoder
    in_speech = ps_get_in_speech(ps);            // test to see if speech is being detected
    if (in_speech && !utt_started)
      utt_started = TRUE;                      // then set the flag
    if (!in_speech && utt_started)
		{                 // if speech has ended and the utt_started flag is true
      ps_end_utt(ps);                          // then mark the end of the utterance
      ad_stop_rec(ad);                         // stop recording
      hyp = ps_get_hyp(ps, NULL);
      return (hyp);
      break;
    }
  }
}

char *record()
{
//	ps_decoder_t 	*ps;                  // create pocketsphinx decoder structure
//	cmd_ln_t 	*config;                  // create configuration structure
//	ad_rec_t 	*ad;                      // create audio recording structure - for use with ALSA functions
//	int16 adbuf[4096];                 // buffer array to hold audio data
//	uint8 utt_started, in_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
//	int32 k;                           // holds the number of frames in the audio buffer
//	char const *hyp;                   // pointer to "hypothesis" (best guess at the decoded result)
	const char *decoded_speech;


	ps = ps_init(config);                                                        // initialize the pocketsphinx decoder
	ad = ad_open_dev("sysdefault", (int)cmd_ln_float32_r(config, "-samprate")); // open default microphone at default samplerate
	while (1)
	{
		decoded_speech = recognize_from_microphone();                 // call the function to capture and decode speech
		printf("You Said: %s\n", decoded_speech);                               // send decoded speech to screen
		return ((char*)decoded_speech);
		break;
  }
	exit(0);
}

int main(int argc, char **argv)
{
  int	sockfd, numbytes;
  char	*output;
  struct 	addrinfo hints, *servinfo, *p;
  int 	rv;
  char 	s[INET6_ADDRSTRLEN];

	if (argc == 1)
	{
		memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
   	hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
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
    while (1)
    {
			      output = (char*)calloc(MAXDATASIZE,sizeof(char));
            output = record();
      			if ((numbytes = send(sockfd, output, MAXDATASIZE - 1, 0)) == -1)
      			{
       	 			perror("send");
       	 			exit(1);
      			}
      			output[numbytes] = '\0';
      			printf("client: sent file successfully\n");
      			close(sockfd);
    		}
	}
	else
    perror("usage: ./client <host.ip.address> || ");
  return 0;
}
