# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parse_json.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/24 16:55:09 by etregoni          #+#    #+#              #
#    Updated: 2017/10/24 16:55:10 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh
S="json/ip_info.json"
D="flite_transcripts/location"

rm -f flite_transcripts/location
grep "city" $S | sed "s/city//g" | tr -d '"' | tr -d ',' | tr -d ':' | tr -d ' ' >> $D
grep "region" $S | sed "s/region//g" | tr -d '"' | tr -d ',' | tr -d ':' | tr -d ' ' >> $D
grep "country" $S | sed "s/country//g" | tr -d '"' | tr -d ',' | tr -d ':' | tr -d ' ' >> $D
