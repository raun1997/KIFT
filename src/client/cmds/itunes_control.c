#include <stdlib.h>
#include <string.h>

int		main(int ac, char **av)
{
	if (!(strcmp(av[1], "play a song")))
		system("say \"playing a song\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to play\'");
	if (!(strcmp(av[1], "pause")))
		system("say \"pausing iTunes\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to pause\'");
	if (!(strcmp(av[1], "next song")))
		system("say \"next song\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to next track\'");
	if (!(strcmp(av[1], "previous song")))
		system("say \"previous song\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to previous track\'");
	if (!(strcmp(av[1], "mute")))
		system("say \"muting iTunes\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to set mute to true\'");
	if (!(strcmp(av[1], "unmute")))
		system("say \"unmuting iTunes\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to set mute to false\'");
	if (!(strcmp(av[1], "stop")))
		system("say \"stopping iTunes\" -v \"Zarvox\" && osascript -e \
				\'tell application \"iTunes\" to stop\'");
}