/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 17:01:12 by iwagner           #+#    #+#             */
/*   Updated: 2017/10/27 15:41:27 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	music_and_stuff(char *hyp, FILE *fp)
{
	if (strstr(hyp, "STAY") && strstr(hyp, "GUARD"))
	{
		system("sh src/client/cmds/brightness.sh guard &");
		fwrite("\tSTAY ON GUARD\n", 1, strlen("\tSTAY ON GUARD\n"), fp);
	}
	else if ((strstr(hyp, "END") && strstr(hyp, "PATROL")) || (strstr(hyp,"SABRE") && strstr(hyp, "MASSACRE")))
	{
		system("say \"Why do you always end all my fun!\" ");
		system(" killall osascript 2>/dev/null & killall afplay 2>/dev/null");
		fwrite("\tEND PATROL\n", 1, strlen("\tEND PATROL\n"), fp);
	}
	else if (strstr(hyp, "KILLING") && (strstr(hyp, "SPREE") || \
		strstr(hyp, "PLAYLIST")))
	{
		system("say \"PUMP UP THE JAMS! PUMP IT UP!\" ");
		system("afplay src/client/audio/pipes.mp3 &");
		fwrite("\tKILLING SPREE PLAYLIST\n", 1, \
			strlen("\tKILLING SPREE PLAYLIST\n"), fp);
	}
}

void	comms(char *hyp, FILE *fp)
{
	if (strstr(hyp, "EMCON"))
	{
		system("say \"Muting\" & osascript -e 'set volume with output muted'");
		fwrite("\tMUTE\n", 1, strlen("\tMUTE\n"), fp);
	}
	else if (strstr(hyp, "NOTIFY") && strstr(hyp, "ENEMIES"))
	{
		system("afplay src/client/audio/t.wav");
		system("say \"North Korea ... Here .. I ... COME!!!!!\"");
		fwrite("\tNOTIFY ENEMIES\n", 1, strlen("\tNOTIFY ENEMIES\n"), fp);
	}
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

void	actions(char *hyp, FILE *fp)
{
	if (strstr(hyp, "HACK") && strstr(hyp, "ELECTION"))
	{
		system("say \"Hack the election... I already did that.\"");
		fwrite("\tHACK ELECTION\n", 1, strlen("\tHACK ELECTION\n"), fp);
	}
	else if (strstr(hyp, "SNEAK") && strstr(hyp, "ATTACK"))
	{
		system("open -a Preview src/client/cmds/winme.jpg");
		system("/usr/bin/osascript -e \'tell application \"Preview\"' -e \"\
			activate\" -e \'tell application \"System Events\"\' -e \'\
			keystroke \"f\"	using {control down, command down}\' \
			-e \"end tell\" -e \"end tell\"");
		system("afplay src/client/cmds/winmesound.m4a");
		fwrite("\tSNEAK ATTACK\n", 1, strlen("\tSNEAK ATTACK\n"), fp);
	}
	else if (strstr(hyp, "SABRE") && (strstr(hyp, "KILL")))
	{
		system("killall say 2>/dev/null");
		system("killall afplay 2>/dev/null");
		system("killall osascript 2>/dev/null");
		system("say \"Okay, hold still.\"");
		fwrite("\tKILL\n", 1, strlen("\tKILL\n"), fp);
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
		fwrite("\tCURRENT LOCATION\n", 1, strlen("\tCURRENT LOCATION\n"), fp);
	}
	else if (strstr(hyp, "CHECK") && strstr(hyp, "HISTORY"))
	{
		system("say \"Reviewing logs.\" & cat logs.log");
		fwrite("\tCHECK HISTORY\n", 1, strlen("\tCHECK HISTORY\n"), fp);
	}
	else if (strstr(hyp, "LAUNCH") && strstr(hyp, "NUKES"))
	{
		system("sh src/client/cmds/nukes.sh");
		fwrite("\tLANUCH NUKES\n", 1, strlen("\tLAUNCH NUKES\n"), fp);
	}
}

void	check2(char *hyp, FILE *fp)
{
	if (strstr(hyp, "WHO") && strstr(hyp, "CONNECTED"))
	{
		system("sh src/client/cmds/user.sh");
		system("ldapsearch -LLL \"(uid=$(whoami))\" cn 2>/dev/null | \
			grep -E '^cn: ' | sed 's/cn: //g' | say");
		fwrite("\tWHO IS CONNECTED\n", 1, strlen("\tWHO IS CONNECTED\n"), fp);
	}
	else if (strstr(hyp, "WEATHER"))
	{
		get_weather("37.5486260, -122.0591160");
		fwrite("\tCHECK WEATHER\n", 1, strlen("\tCHECK WEATHER\n"), fp);
	}
	else if (strstr(hyp, "TRAFFIC"))
	{
		get_traffic();
		fwrite("\tCHECK TRAFFIC\n", 1, strlen("\tCHECK TRAFFIC\n"), fp);
	}
	else if (strstr(hyp, "DEE") && strstr(hyp, "LONG"))
	{
		system("say \"Get your shit graded.\"");
		fwrite("\tDAYS LEFT TO GET THIS GRADED\n", 1, \
			strlen("\tDAYS LET TO GET THIS GRADED\n"), fp);
	}
}
