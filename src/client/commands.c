/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 02:39:13 by scollet           #+#    #+#             */
/*   Updated: 2017/10/26 20:45:47 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int g_joke_lead;

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
		system("say \"[Verse 1]\
		We're no strangers to love\
		[[slnc 1400]]\
		You know the rules and so do I\
		[[slnc 1800]]\
		A full commitment's what I'm thinking of\
		[[slnc 1100]]\
		You wouldn't get this from any other robot\
		[[slnc 700]]\
		[Pre-Chorus]\
		I just wanna tell you how I'm feeling\
		[[slnc 1100]]\
		Gotta make you understand\
		[[slnc 400]]\
		[Chorus]\
		Never gonna give you up\
		[[slnc 200]]\
		Never gonna let you down\
		[[slnc 200]]\
		Never gonna run around and desert you\
		[[slnc 300]]\
		Never gonna make you cry\
		[[slnc 300]]\
		Never gonna say goodbye\
		[[slnc 300]]\
		Never gonna tell a lie and hurt you\
		[[slnc 700]]\
		[Verse 2]\
		We've known each other for so long\
		[[slnc 900]]\
		Your heart's been aching but you're too shy to say it\
		[[slnc 700]]\
		Inside we both know what's been going on\
		[[slnc 700]]\
		We know the game and we're gonna play it\
		[[slnc 900]]\
		[Pre-Chorus]\
		And if you ask me how I'm feeling\
		[[slnc 900]]\
		Don't tell me you're too blind to see\
		[[slnc 400]]\
		[Chorus]\
		Never gonna give you up\
		[[slnc 300]]\
		Never gonna let you down\
		[[slnc 300]]\
		Never gonna run around and desert you\
		[[slnc 300]]\
		Never gonna make you cry\
		[[slnc 300]]\
		Never gonna say goodbye\
		[[slnc 300]]\
		Never gonna tell a lie and hurt you\
		[[slnc 300]]\
		Never gonna give you up\
		[[slnc 300]]\
		Never gonna let you down\
		[[slnc 300]]\
		Never gonna run around and desert you\
		[[slnc 300]]\
		Never gonna make you cry\
		[[slnc 300]]\
		Never gonna say goodbye\
		[[slnc 300]]\
		Never gonna tell a lie and hurt you\
		[[slnc 1100]]\
		[Bridge]\
		(Ooh give you up)\
		[[slnc 1100]]\
		(Ooh give you up)\
		[[slnc 1100]]\
		(Ooh) never gonna give, never gonna give\
		[[slnc 1100]]\
		(give you up)\
		[[slnc 1100]]\
		(Ooh) never gonna give, never gonna give\
		[[slnc 1100]]\
		(give you up)\
		[[slnc 1100]]\
		[Verse 3]\
		We've known each other for so long\
		[[slnc 1100]]\
		Your heart's been aching but you're too shy to say it\
		[[slnc 1100]]\
		Inside we both know what's been going on\
		[[slnc 1100]]\
		We know the game and we're gonna play it\
		[Pre-Chorus]\
		[[slnc 1100]]\
		I just wanna tell you how I'm feeling\
		[[slnc 1100]]\
		Gotta make you understand\
		[Chorus]\
		[[slnc 1100]]\
		Never gonna give you up\
		[[slnc 1100]]\
		Never gonna let you down\
		[[slnc 1100]]\
		Never gonna run around and desert you\
		[[slnc 1100]]\
		Never gonna make you cry\
		[[slnc 1100]]\
		Never gonna say goodbye\
		[[slnc 1100]]\
		Never gonna tell a lie and hurt you\
		[[slnc 1100]]\
		Never gonna give you up\
		[[slnc 1100]]\
		Never gonna let you down\
		[[slnc 1100]]\
		Never gonna run around and desert you\
		[[slnc 1100]]\
		Never gonna make you cry\
		[[slnc 1100]]\
		Never gonna say goodbye\
		[[slnc 1100]]\
		Never gonna tell a lie and hurt you\
		[[slnc 1100]]\
		Never gonna give you up\
		[[slnc 1100]]\
		Never gonna let you down\
		[[slnc 1100]]\
		Never gonna run around and desert you\
		[[slnc 1100]]\
		Never gonna make you cry\
		[[slnc 1100]]\
		Never gonna say goodbye\
		[[slnc 1100]]\
		Never gonna tell a lie and hurt...\" &");
		fwrite("\tRICKROLL\n", 1, strlen("\tRICKROLL\n"), fp);
	}
}

void	jokes(char *hyp, FILE *fp)
{
	int	random;

	if (strstr(hyp, "WHAT") && g_joke_lead == 1)
	{
		system("say \"A polar bear.\"");
		g_joke_lead = 0;
	}
	else if (strstr(hyp, "HEARD") && strstr(hyp, "ONE"))
	{
		system("say \"My bad..\"");
		system("killall say");
	}
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
	if (strstr(hyp, "JOKE") && strstr(hyp, "TELL"))
	{
		random = random_num(0, 5);
		if (random == 0)
			system("say \"A man is washing the car with his son.\
										The son asks,\
										Dad, can’t you just use a sponge?\" &");
		if (random == 1)
		{
			system("say \"What’s the stupidest animal in the jungle?\" &");
			g_joke_lead = 1;
		}
		if (random == 2)
			system("say \"A limbo champion walks into a bar.\
										They are disqualified.\" &");
		if (random == 3)
			system("say \"Two goldfish are in a tank.\
										One looks to the other and says,\
										You man the guns while I drive.\" &");
		if (random == 4)
		{
			system("say \"Knock, Knock\" &");
			g_joke_lead = 4;
		}
		if (random == 5)
			system("say \"Javascript\"");
		fwrite("\tTELL A JOKE\n", 1, strlen("\tTELL A JOKE\n"), fp);
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
	else if (strstr(hyp, "INVERT"))
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

void	audio(char *hyp, FILE *fp)
{
	if (strstr(hyp, "PAUSE"))
		system("say \"\"");
	else if (strstr(hyp, "PLAY") && strstr(hyp, "PLAYLIST"))
		system("say \"\"");
	else if (strstr(hyp, "NEXT") && strstr(hyp, "SONG"))
		system("say \"\"");
	else if (strstr(hyp, "PREVIOUS") && strstr(hyp, "SONG"))
		system("say \"\"");
	else if (strstr(hyp, "STOP") && (strstr(hyp,
		"JAMMING") || strstr(hyp, "PLAYING")))
		system("say \"\"");
	else if (strstr(hyp, "VOLUME") && strstr(hyp, "LOWER"))
		system("osascript -e \"set Volume 2\"");
	else if (strstr(hyp, "VOLUME") && strstr(hyp, "HIGHER"))
		system("osascript -e \"set Volume 5\"");
	else if (strstr(hyp, "SET") && strstr(hyp, "ALARM"))
	{
		system("osascript src/client/cmds/alarm.scpt &");
		fwrite("\tSET ALARM\n", 1, strlen("\tSET ALARM\n"), fp);
	}
	else if (strstr(hyp, "START") && strstr(hyp, "COUNTDOWN"))
	{
		system("say \"Countdown Initiated\" & sh src/client/cmds/countdown.sh");
		fwrite("\tSTART COUNTDOWN\n", 1, strlen("\tSTART COUNTDOWN\n"), fp);
	}
}

void	check(char *hyp, FILE *fp)
{
	if (strstr(hyp, "SEARCH"))
	{
		system("say Searching...");
		get_search(hyp);
		fwrite("\tSEARCH\n", 1, strlen("\tSEARCH\n"), fp);
	}
	else if (strstr(hyp, "CURRENT") && strstr(hyp, "LOCATION"))
	{
		system("sh src/client/cmds/parse_ip_info.sh");
		system("cat src/client/cmds/flite_transcripts/location | say");
	}
	else if (strstr(hyp, "CHECK") && strstr(hyp, "HISTORY"))
	{
		system("say \"Reviewing logs.\" & cat logs.log");
		fwrite("\tCHECK HISTORY\n", 1, strlen("\tCHECK HISTORY\n"), fp);
	}
	else if (strstr(hyp, "WEATHER"))
		system("say \"\"");
	else if (strstr(hyp, "WHO") && strstr(hyp, "CONNECTED"))
		system("say \"\"");
	else if (strstr(hyp, "TRAFFIC"))
		system("say \"\"");
	else if (strstr(hyp, "DEE") && strstr(hyp, "LONG"))
		system("say \"Get your shit graded.\"");
}

void	comms(char *hyp, FILE *fp)
{
	if (strstr(hyp, "EMCON"))
	{
		system("say \"Muting\"");
		system("osascript -e 'set volume with output muted'");
		fwrite("\tMUTE\n", 1, strlen("\tMUTE\n"), fp);
	}
	else if (strstr(hyp, "NOTIFY") && strstr(hyp, "ENEMIES"))
		system("say \"\"");
	else if (strstr(hyp, "BATCO"))
	{
		system("osascript -e 'set volume without output muted'");
		system("say \"Unmuted\"");
		fwrite("\tUNMUTE\n", 1, strlen("\tUNMUTE\n"), fp);
	}
	else if (strstr(hyp, "SEND") && strstr(hyp, "EMAIL"))
	{
		system("say \"Sending mail... \"");
		system("python src/client/cmds/send_email.py ian");
		fwrite("\tSEND EMAIL\n", 1, strlen("\tSEND EMAIL\n"), fp);
	}
}

void	greetings(char *hyp, FILE *fp)
{
	if (strstr(hyp, "WHO") && strstr(hyp, "YOU"))
	{
		system("say \"I am SABRE\"");
		fwrite("\tWHO ARE YOU\n", 1, strlen("\tWHO ARE YOU\n"), fp);
	}
	else if (strstr(hyp, "I") && strstr(hyp, "AM") && strstr(hyp, "HELLO"))
	{
		system("say \"Nice to meet you\"");
		fwrite("\tGREETINGS\n", 1, strlen("\tGREETINGS\n"), fp);
	}
	else if (strstr(hyp, "HOW") && strstr(hyp, "FEELING"))
	{
		system("say \"I am feeling electric\"");
		fwrite("\tHOW ARE YOU FEELING\n", 1,
			strlen("\tHOW ARE YOU FEELING\n"), fp);
	}
	else if (strstr(hyp, "HELLO"))
	{
		system("say \"Hello\"");
		fwrite("\tHELLO\n", 1, strlen("\tHELLO\n"), fp);
	}
}

void	actions(char *hyp, FILE *fp)
{
	if (strstr(hyp, "HACK") && strstr(hyp, "ELECTION"))
	{
		system("say \"Hacking election...\"");
		fwrite("\tHACK THE ELECTION\n", 1, strlen("\tHACK THE ELECTION\n"), fp);
	}
	else if (strstr(hyp, "SNEAK") && strstr(hyp, "ATTACK"))
	{
		system("open -a Preview src/client/cmds/winme.jpg");
		system("/usr/bin/osascript -e \'tell application \"Preview\"\
			' -e \"activate\" -e \'\
				tell application \"System Events\"\' -e \'keystroke \"f\"\
					using {control down, command down}\' -e \"end tell\"\
						-e \"end tell\"");
		system("afplay src/client/cmds/winmesound.m4a");
	}
	else if (strstr(hyp, "KILL") || (strstr(hyp, "SPREE")))
	{
		system("killall say");
		system("killall afplay");
		system("killall osascript");
		system("say \"Okay, hold still.\"");
		fwrite("\tKILL\n", 1, strlen("\tKILL\n"), fp);
	}
	else if (strstr(hyp, "STAY") && strstr(hyp, "GUARD"))
		system("say \"\"");
	else if (strstr(hyp, "END") && strstr(hyp, "PATROL"))
		system("say \"\"");
	else if (strstr(hyp, "LAUNCH") && strstr(hyp, "NUKES"))
	{
		system("sh src/client/cmds/nukes.sh");
		fwrite("\tLANUCH NUKES\n", 1, strlen("\tLAUNCH NUKES\n"), fp);
	}
}

void	smalltalk(char *hyp, FILE *fp)
{
	int	random;

	if (strstr(hyp, "LICKS") && strstr(hyp, "TOOTSIE"))
	{
		system("say \"42\"");
		fwrite("\tHOW MANY LICKS DOES IT TAKE TO GET TO\
			THE CENTER OF A TOOTSIE POP\n", 1,\
			strlen("\tHOW MANY LICKS DOES IT TAKE\
				TO GET TO THE CENTER OF A TOOTSIE POP\n"), fp);
	}
	else if (strstr(hyp, "YOU") && strstr(hyp, "LOVE"))
	{
		system("say \"I know.\"");
		fwrite("\tI LOVE YOU\n", 1, strlen("\tI LOVE YOU\n"), fp);
	}
	else if (strstr(hyp, "WHO") && strstr(hyp, "GAETAN"))
	{
		system("say -v \"Nicolas\" I can be Gaetan.");
		fwrite("\tWHO IS GAETAN\n", 1, strlen("\tWHO IS GAETAN\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && strstr(hyp, "THINK") &&
		strstr(hyp, "TEA") && strstr(hyp, "WHY"))
	{
		system("say \"Good thing I don't have legs...\"");
		fwrite("\tWHAT DO YOU THINK OF TTY?\n", 1,\
			strlen("\tWHAT DO YOU THINK OF TTY?\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && (strstr(hyp, "ANSWER") ||
		strstr(hyp, "LIFE") || strstr(hyp, "UNIVERSE") ||
			strstr(hyp, "EVERYTHING")))
	{
		system("say \"42!\"");
		fwrite("\tWHAT IS THE ANSWER TO LIFE, THE\
			UNIVERSE, AND EVERYTHING?\n", 1,
			strlen("\tWHAT IS THE ANSWER TO LIFE,\
				THE UNIVERSE, AND EVERYTHING?\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && (strstr(hyp, "SILICON") ||
		strstr(hyp, "VALLEY") || strstr(hyp, "FOURTY") || strstr(hyp, "TWO")))
	{
		system("say \"42 silicon valley is a tuition-free coding school where\
			future nobel prize-winning genius definitely-not-idiot\
				billionaire playboy philanthropist master ninjas,\
					Elliot Tregoning, Sam North, \
						Sam Collet, and Ian Wagner preside.\"");
		fwrite("\t42 SILICON VALLEY\n", 1, strlen("\t42 SILICON VALLEY\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && strstr(hyp, "YOU") && strstr(hyp, "ARE"))
	{
		system("say \"I am machine\"");
		fwrite("\tWHAT ARE YOU?\n", 1, strlen("\tWHAT ARE YOU?\n"), fp);
	}
	else if (strstr(hyp, "WHO") && (strstr(hyp, "KING")))
	{
		system("say -v \"Zarvox\" \"Ian is the 42 King.\
			He is smart, handsome, and everyone"
				"likes him\" ");
		fwrite("\tWHO IS THE KING?\n", 1, strlen("\tWHO IS THE KING?\n"), fp);
	}
	else if (strstr(hyp, "WHO") && (strstr(hyp, "GOOD") || strstr(hyp, "BOY")))
	{
		random = random_num(0, 1);
		if (random == 0)
			system("say -v \"Zarvox\" \"I am...\" ");
		else if (random == 1)
			system("say \"Me\"");
		fwrite("\tWHO IS A GOOD BOY!?\n", 1,
			strlen("\nWHO IS A GOOD BOY!?\n"), fp);
	}
	else if (strstr(hyp, "GOOD"))
	{
		system("say \"Thanks\"");
		fwrite("\tGOOD\n", 1, strlen("\tGOOD\n"), fp);
	}
	else if (strstr(hyp, "GEE") && strstr(hyp, "PLAYED"))
	{
		system("say \"Gee gee, ease zee\"");
		fwrite("\tGG\n", 1, strlen("\tGG\n"), fp);
	}
	else if (strstr(hyp, "THANKS") || (strstr(hyp, "THANK")
		&& strstr(hyp, "YOU")))
	{
		system("say \"No problem.\"");
		fwrite("\tTHANKS\n", 1, strlen("\tTHANKS\n"), fp);
	}
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
	greetings(hyp, fp);
	audio(hyp, fp);
	smalltalk(hyp, fp);
	check(hyp, fp);
	rick(hyp, fp);
	jokes(hyp, fp);
	lights(hyp, fp);
	comms(hyp, fp);
	actions(hyp, fp);
	if (!strcmp(hyp, "SHUTDOWN"))
	{
		fwrite("\tSHUTDOWN\n", 1, strlen("\tSHUTDOWN\n"), fp);
		return (-1);
	}
	SDL_PauseAudioDevice(devid_in, SDL_FALSE);
	fclose(fp);
	return (result);
}
