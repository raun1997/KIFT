-- **************************************************************************** --
--                                                                              --
--                                                         :::      ::::::::    --
--    alarm.scpt                                         :+:      :+:    :+:    --
--                                                     +:+ +:+         +:+      --
--    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         --
--                                                 +#+#+#+#+#+   +#+            --
--    Created: 2017/10/19 22:34:28 by etregoni          #+#    #+#              --
--    Updated: 2017/10/19 22:34:36 by etregoni         ###   ########.fr        --
--                                                                              --
-- **************************************************************************** --

on run argv
	if (item 1 of argv as string = "up") then
		tell application "System Events"
			key code 144
			say "brightness increased" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "down") then
		tell application "System Events"
			key code 145
			say "brightness decreased" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "max") then
		tell application "System Events"
			repeat 16 times
				key code 144
			end repeat
			say "brightness increased to highest setting" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "min") then
		tell application "System Events"
			repeat 16 times
				key code 145
			end repeat
			say "brightness decreased to lowest setting" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "more") then
		tell application "System Events"
			repeat 3 times
				key code 144
			end repeat
			say "brightness increased" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "less") then
		tell application "System Events"
			repeat 3 times
				key code 145
			end repeat
			say "brightness decreased" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "less") then
		tell application "System Events"
			repeat 3 times
				key code 145
			end repeat
			say "brightness decreased" using "Zarvox"
		end tell
	else if (item 1 of argv as string = "off") then
		do shell script "pmset displaysleepnow"
		say "display turned off" using "Zarvox"

	else if (item 1 of argv as string = "on") then
		do shell script "caffeinate -u -t 2"
		say "display turned on" using "Zarvox"
	end if
end run
