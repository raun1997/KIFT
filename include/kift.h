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
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
//#include "portaudio.h"
// Leaving portaudio out until we have a use for it, build intructions
// depend on use case.
#include "audio.h"

# define AUDIO_PATH "src/client/audio/"
# define BACKLOG 16
# define PORT "4242"
# define NAME "SELF-AWARE-BATTLE-ROBOT"
# define IP "10.112.6.9"
# define MAXDATASIZE 100
# define S_RATE (44100)
# define BUF_SIZE (S_RATE * 2)

int   example(char *str);
char	*get_ip_str(void);
const char *recognize_from_microphone();

#endif
