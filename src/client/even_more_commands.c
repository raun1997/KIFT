/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 17:01:12 by iwagner           #+#    #+#             */
/*   Updated: 2017/10/27 15:44:32 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int	g_joke_lead;

void	audio(char *hyp, FILE *fp)
{
	if (strstr(hyp, "VOLUME") && strstr(hyp, "DOWN"))
	{
		system("osascript -e 'set Volume 2'");
		fwrite("\tVOLUME DOWN\n", 1, strlen("\tVOLUME DOWN\n"), fp);
	}
	else if (strstr(hyp, "VOLUME") && strstr(hyp, "UP"))
	{
		system("osascript -e 'set Volume 5'");
		fwrite("\tVOLUME UP\n", 1, strlen("\tVOLUME UP\n"), fp);
	}
	else if (strstr(hyp, "SET") && strstr(hyp, "ALARM"))
	{
		system("osascript src/client/cmds/alarm.scpt &");
		fwrite("\tSET ALARM\n", 1, strlen("\tSET ALARM\n"), fp);
	}
	else if (strstr(hyp, "START") && strstr(hyp, "COUNTDOWN"))
	{
		system("say \"Countdown Initiated\" & sh src/client/cmds/countdn.sh");
		fwrite("\tSTART COUNTDOWN\n", 1, strlen("\tSTART COUNTDOWN\n"), fp);
	}
}

void	lights(char *hyp, FILE *fp)
{
	if (strstr(hyp, "UP") && strstr(hyp, "LIGHTS"))
	{
		system("sh src/client/cmds/brightness.sh up");
		fwrite("\tLIGHTS UP\n", 1, strlen("\tLIGHTS UP\n"), fp);
	}
	else if (strstr(hyp, "DOWN") && strstr(hyp, "LIGHTS"))
	{
		system("sh src/client/cmds/brightness.sh down");
		fwrite("\tLIGHTS DOWN\n", 1, strlen("\tLIGHTS DOWN\n"), fp);
	}
	else if (strstr(hyp, "DIM"))
	{
		system("sh src/client/cmds/brightness.sh less");
		fwrite("\tLIGHTS DIM\n", 1, strlen("\tLGIHTS DIM\n"), fp);
	}
	else if (strstr(hyp, "BRIGHTER"))
	{
		system("sh src/client/cmds/brightness.sh more");
		fwrite("\tLIGHTS BRIGHTER\n", 1, strlen("\tLIGHTS BRIGHTER\n"), fp);
	}
}

void	lights2(char *hyp, FILE *fp)
{
	if (strstr(hyp, "INVERT"))
	{
		system("osascript -e 'tell application \"System Events\"' \
			-e 'key code 28 using {control down, option down, command down}' \
				-e 'end tell'");
		fwrite("\tINVERT COLORS\n", 1, strlen("\tINVERT COLORS\n"), fp);
	}
	else if (strstr(hyp, "GO") && strstr(hyp, "DARK"))
	{
		system("sh src/client/cmds/brightness.sh min");
		fwrite("\tGO DARK\n", 1, strlen("\tGO DARK\n"), fp);
	}
	else if (strstr(hyp, "BLIND"))
	{
		system("sh src/client/cmds/brightness.sh max");
		fwrite("\tBLIND THE ENEMY\n", 1, strlen("\tBLIND THE ENEMY\n"), fp);
	}
}

void	jokes2(char *hyp, FILE *fp)
{
	int	random;

	random = random_num(0, 5);
	if (random == 0)
		system("say \"A man is washing the car with his son.\
			The son asks,   Dad, can’t you just use a sponge?\" &");
	else if (random == 1)
	{
		system("say \"What’s the stupidest animal in the jungle?\" &");
		g_joke_lead = 1;
	}
	else if (random == 2)
		system("say \"A limbo champion walks into a bar.\
									They are disqualified.\" &");
	else if (random == 3)
		system("say \"Two goldfish are in a tank. One looks to the other and\
			says, You man the guns while I drive.\" &");
	else if (random == 5)
		system("say \"Javascript\"");
	else
	{
		system("say \"Knock, Knock\" &");
		g_joke_lead = 4;
	}
}

void	jokes(char *hyp, FILE *fp)
{
	if (strstr(hyp, "WHAT") && g_joke_lead == 1)
	{
		system("say \"A polar bear.\"");
		g_joke_lead = 0;
	}
	else if (strstr(hyp, "HEARD") && strstr(hyp, "ONE"))
		system("say \"My bad..\"");
	else if (strstr(hyp, "THERE") && g_joke_lead == 4)
	{
		system("say \"Sabre.\"");
		g_joke_lead = 5;
	}
	else if (strstr(hyp, "SABRE") && strstr(hyp, "WHO") && g_joke_lead == 5)
	{
		system("say \"How do you not remember me, motherfucker.\"");
		g_joke_lead = 0;
	}
	else if (strstr(hyp, "JOKE") && strstr(hyp, "TELL"))
	{
		jokes2(hyp, fp);
		fwrite("\tTELL A JOKE\n", 1, strlen("\tTELL A JOKE\n"), fp);
	}
}
