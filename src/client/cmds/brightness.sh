# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    brightness.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/23 15:56:19 by etregoni          #+#    #+#              #
#    Updated: 2017/10/23 15:56:22 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

CMD_PTH="./src/client/cmds/brightness.scpt"

if [ "$#" == 1 ] ; then
	# Check brightness level, if already at min/max, replies as such and exits
	CMD=$(nvram backlight-level | awk '{print $2}')
	echo $CMD
	if [ $1 == "up" ] ; then
		if [ $CMD == "I%cb" ] ; then
			say -v "Zarvox" brightness is already at the highest setting
			exit
		fi
	elif [ $1 == "down" ] ; then
		if [ $CMD == "%10%02" ] ; then
			say -v "Zarvox" brightness is already at the lowest setting
			exit
		fi
	elif [ $1 == "more" ] ; then
		if [ $CMD == "I%cb" ] ; then
			say -v "Zarvox" brightness is already at the highest setting
			exit
		fi
	elif [ $1 == "less" ] ; then
		if [ $CMD == "%10%02" ] ; then
			say -v "Zarvox" brightness is already at the lowest setting
			exit
		fi
	elif [ $1 == "max" ] ; then
		if [ $CMD == "I%cb" ] ; then
			say -v "Zarvox" brightness is already at the highest setting
			exit
		fi
	elif [ $1 == "min" ] ; then
		if [ $CMD == "%10%02" ] ; then
			say -v "Zarvox" brightness is already at the lowest setting
			exit
		fi
	fi

	# Change brightness level up or down
	if [ $1 == "up" ] ; then
		osascript $CMD_PTH up
	elif [ $1 == "down" ] ; then
		osascript $CMD_PTH down
	elif [ $1 == "max" ] ; then
		osascript $CMD_PTH max
	elif [ $1 == "min" ] ; then
		osascript $CMD_PTH min
	elif [ $1 == "more" ] ; then
		osascript $CMD_PTH more
	elif [ $1 == "less" ] ; then
		osascript $CMD_PTH less
	elif [ $1 == "off" ] ; then
		osascript $CMD_PTH off
	elif [ $1 == "on" ] ; then
		osascript $CMD_PTH on
	elif [ $1 == "guard" ] ; then
		osascript $CMD_PTH guard
	fi
else
	echo invalid arg count
fi
