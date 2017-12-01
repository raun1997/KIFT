/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_conn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 00:02:44 by scollet           #+#    #+#             */
/*   Updated: 2017/10/27 15:18:38 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

static int	read_data(int16 *buf, int num_samples, int socket)
{
	char	*buf_pointer;
	int		num_bytes;
	int		rc;

	buf_pointer = (char*)buf;
	num_bytes = num_samples * sizeof(int16);
	while (num_bytes)
	{
		rc = recv(socket, buf_pointer, num_bytes, 0);
		if (rc < 0)
			return (rc);
		if (rc > 0)
		{
			num_bytes -= rc;
			buf_pointer += rc;
			continue ;
		}
		return (0);
	}
	return (num_samples);
}

static int	read_samples(ps_decoder_t *g_ps, int num_samples, int socket)
{
	int16	client_message[BUF_SIZE];
	uint8	in_speech;
	int		rc;

	while (num_samples)
	{
		rc = read_data(client_message,
			(num_samples > BUF_SIZE) ? BUF_SIZE : num_samples, socket);
		if (rc > 0)
		{
			in_speech = 0;
			ps_process_raw(g_ps, client_message, rc, FALSE, FALSE);
			in_speech = ps_get_in_speech(g_ps);
			if (in_speech && (g_utt_state == UTT_STATE_WAITING))
				g_utt_state = UTT_STATE_LISTENING;
			if (!in_speech && (g_utt_state == UTT_STATE_LISTENING))
				g_utt_state = UTT_STATE_FINISHED;
			num_samples -= rc;
		}
		else
			return (rc);
	}
	return (1);
}

int			go(Package *pack, int32 num_samples)
{
	int rc;

	while (g_utt_state != UTT_STATE_FINISHED)
	{
		pack->read_size = 0;
		rc = recv(pack->new_fd, &num_samples, sizeof(num_samples), 0);
		if (rc <= 0)
		{
			printf("Error or disconnected (%d) errno = %d\n", rc, errno);
			g_utt_state = UTT_STATE_ERROR;
			break ;
		}
		if (num_samples)
		{
			pack->read_size = read_samples(g_ps, num_samples, pack->new_fd);
			if (pack->read_size != 1)
			{
				printf("Error reading samples: %d\n", pack->read_size);
				g_utt_state = UTT_STATE_ERROR;
			}
		}
	}
	return (0);
}

int			set(Package *pack)
{
	int32 num_samples;

	while (g_utt_state != UTT_STATE_QUIT && !(num_samples = 0))
	{
		pack->rv = ps_start_utt(g_ps);
		g_utt_state = UTT_STATE_WAITING;
		go(pack, num_samples);
		if (g_utt_state == UTT_STATE_FINISHED)
		{
			pack->rv = ps_end_utt(g_ps);
			pack->hyp = ps_get_hyp(g_ps, &pack->score);
			printf("Recognized: %s\n", pack->hyp);
			if (pack->hyp)
				send(pack->new_fd, pack->hyp, strlen(pack->hyp), 0);
			if (pack->hyp && strstr(pack->hyp, "SHUTDOWN"))
				g_utt_state = UTT_STATE_QUIT;
			else
				g_utt_state = UTT_STATE_WAITING;
		}
		else if (printf("Terminating connection due to error.\n"))
			break ;
	}
	system("killall say 2>/dev/null & killall Electron 2>/dev/null");
	system("say Goodbye");
	return (0);
}

int			ready(Package *pack)
{
	if (!fork())
	{
		printf("Preparing to recieve ... \n");
		g_config = cmd_ln_init(NULL, ps_args(), TRUE,
							"-hmm", "./sabr/en-us-adapt",
							"-lm", "./sabr/model/sabr.lm",
							"-dict", "./sabr/model/sabr.dict",
							"-logfn", "sabr/kift.log",
							NULL);
		if (g_config == NULL)
		{
			perror("g_config object");
			return (-1);
		}
		g_ps = ps_init(g_config);
		if (g_ps == NULL)
		{
			perror("recognizer");
			return (-1);
		}
		set(pack);
		ps_free(g_ps);
		cmd_ln_free_r(g_config);
	}
	return (0);
}
