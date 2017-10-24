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

if [ "$#" == 1 ] ; then
	# Check brightness level, if already at min/max, replies as such and exits
	CMD=$(brightness -l | grep brightness | sed 's/.* //')
	if [ $1 == "up" ] ; then
		if ((`bc <<< "$CMD>=1.0"`)) ; then
			say -v "Zarvox" brightness is already at the highest setting
			exit
		fi
	elif [ $1 == "down" ] ; then
		if ((`bc <<< "$CMD<=.009"`)) ; then
			say -v "Zarvox" brightness is already at the lowest setting
			exit
		fi
	elif [ $1 == "more" ] ; then
		if ((`bc <<< "$CMD>=1.0"`)) ; then
			say -v "Zarvox" brightness is already at the highest setting
			exit
		fi
	elif [ $1 == "less" ] ; then
		if ((`bc <<< "$CMD<=.009"`)) ; then
			say -v "Zarvox" brightness is already at the lowest setting
			exit
		fi
	elif [ $1 == "max" ] ; then
		if ((`bc <<< "$CMD>=1.0"`)) ; then
			say -v "Zarvox" brightness is already at the highest setting
			exit
		fi
	elif [ $1 == "min" ] ; then
		if ((`bc <<< "$CMD<=.009"`)) ; then
			say -v "Zarvox" brightness is already at the lowest setting
			exit
		fi
	fi

	# Change brightness level up or down
	if [ $1 == "up" ] ; then
		osascript brightness.scpt up
	elif [ $1 == "down" ] ; then
		osascript brightness.scpt down
	elif [ $1 == "max" ] ; then
		osascript brightness.scpt max
	elif [ $1 == "min" ] ; then
		osascript brightness.scpt min
	elif [ $1 == "more" ] ; then
		osascript brightness.scpt more
	elif [ $1 == "less" ] ; then
		osascript brightness.scpt less
	elif [ $1 == "off" ] ; then
		osascript brightness.scpt off
	elif [ $1 == "on" ] ; then
		osascript brightness.scpt on
	fi
else
	echo invalid arg count
fi
