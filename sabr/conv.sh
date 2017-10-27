# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conv.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/26 23:34:16 by scollet           #+#    #+#              #
#    Updated: 2017/10/26 23:36:53 by scollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

mv ../../../Downloads/TAR* ./model/
tar -zxf model/TAR*
rm -f model/TAR*
mv model/*.dic model/sabr.dict
mv model/*.lm model/sabr.lm
mv model/*.log_pronounce model/sabre.log_pronounce
mv model/*.sent model/sabre.sent
mv model/*.vocab model/sabr.vocab
