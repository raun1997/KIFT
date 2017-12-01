/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 02:39:13 by scollet           #+#    #+#             */
/*   Updated: 2017/10/27 01:26:00 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int		random_num(int min, int max)
{
	int	diff;

	diff = max - min;
	return ((int)(((double)(diff + 1) / RAND_MAX) * rand() + min));
}

void	rick(char *hyp, FILE *fp)
{
	if (strstr(hyp, "RICKROLL") && strstr(hyp, "SABRE"))
	{
		system("open \"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" &");
		sleep(18);
		system("cat src/client/cmds/rickroll.txt | say");
		fwrite("\tRICKROLL\n", 1, strlen("\tRICKROLL\n"), fp);
	}
}

void	command_groups(char *hyp, FILE *fp)
{
	greetings(hyp, fp);
	audio(hyp, fp);
	smalltalk(hyp, fp);
	smalltalk2(hyp, fp);
	smalltalk3(hyp, fp);
	smalltalk4(hyp, fp);
	check(hyp, fp);
	check2(hyp, fp);
	rick(hyp, fp);
	music_and_stuff(hyp, fp);
	jokes(hyp, fp);
	lights(hyp, fp);
	lights2(hyp, fp);
	comms(hyp, fp);
	actions(hyp, fp);
}

int		parse_reply(char *hyp, int devid_in)
{
	FILE	*fp;
	int		result;
	char	*com;
	char	*wr;

	result = 0;
	fp = fopen("logs.log", "ab+");
	wr = strndup(strcat(hyp, "\n"), strlen(hyp));
	fwrite(wr, 1, strlen(wr), fp);
	SDL_PauseAudioDevice(devid_in, SDL_TRUE);
	command_groups(hyp, fp);
	if (!strcmp(hyp, "SHUTDOWN"))
	{
		fwrite("\tSHUTDOWN\n", 1, strlen("\tSHUTDOWN\n"), fp);
		return (-1);
	}
	SDL_PauseAudioDevice(devid_in, SDL_FALSE);
	fclose(fp);
	return (result);
}
