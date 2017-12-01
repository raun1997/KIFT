# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    email_confirmation.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/23 17:42:03 by etregoni          #+#    #+#              #
#    Updated: 2017/10/23 17:42:05 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

elliot="Elliot Tregoning"
ian="Ian Wagner"
scollet="Sam Collet"
snorth="Sam North"
if [ "$#" == 1 ] ; then
	if [ $1 == "elliot" ] ; then
		say -v "Zarvox" email was sent successfully to $elliot
	elif [ $1 == "ian" ] ; then
		say -v "Zarvox" email was sent successfully to $ian
	elif [ $1 == "scollet" ] ; then
		say -v "Zarvox" email was sent successfully to $scollet
	elif [ $1 == "snorth" ] ; then
		say -v "Zarvox" email was sent successfully to $snorth
	elif [ $1 == "team" ] ; then
		say -v "Zarvox" email was sent successfully to the whole team
	fi
else
	echo Invalid argument count
fi
