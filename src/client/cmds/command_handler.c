/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:54:05 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/24 19:54:10 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// voice commands need some work for new transcriptions
void command_handler(char *command) {
	if (strcmp(command, "send email") == 0)
		system("python ./src/client/cmds/send_email.py elliot");
	else if (strcmp(command, "launch the nukes") == 0)
		system("sh ./src/client/cmds/nukes.sh");
	else if (strcmp(command, "go dark") == 0)
		system("sh ./src/client/cmds/brightness.sh min");
	else if (strcmp(command, "blind the enemy") == 0)
		system("sh ./src/client/cmds/brightness.sh max");
	else if (strcmp(command, "shutdown") == 0)
		system("sh ./src/client/cmds/brightness.sh off");
	else if (strcmp(command, "tell me a joke") == 0)
		system("say -v \"Zarvox\" \"Ian is smart, handsome, and everyone"
		"likes him\"");
}
