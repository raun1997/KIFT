# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    email.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/20 13:54:18 by etregoni          #+#    #+#              #
#    Updated: 2017/10/20 13:54:24 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python
import smtplib
import sys
import os
from email.mime.multipart import MIMEMultipart
from email.MIMEText import MIMEText

if len(sys.argv) == 2:
	try:
		fromaddr = "self.aware.battle.robot@gmail.com"
		single = ["elliot.tregoning@gmail.com", "enwagner@gmail.com", "samuelpcollet@gmail.com", "samuelrnorth@gmail.com"]
		team = single[0] + ", " + single[1] + ", " + single[2] + ", " + single[3]
		if sys.argv[1] == "elliot":
			toaddr = single[0]
		elif sys.argv[1] == "ian":
			toaddr = single[1]
		elif sys.argv[1] == "scollet":
			toaddr = single[2]
		elif sys.argv[1] == "snorth":
			toaddr = single[3]
		elif sys.argv[1] == "team":
			toaddr = team
		msg = MIMEMultipart()
		msg['From'] = fromaddr
		msg['To'] = toaddr
		msg['Subject'] = "S.A.B.R. Alert"

		body = "You have been targeted by the self-aware battle robot."
		msg.attach(MIMEText(body, 'plain'))

		server = smtplib.SMTP('smtp.gmail.com', 587)
		server.starttls()
		server.login(fromaddr, "sabrkift")
		text = msg.as_string()
		try:
			server.sendmail(fromaddr, toaddr, text)
		finally:
			server.quit()
	except Exception, exc:
		sys.exit( "Sending mail failed; %s" % str(exc) )
	else:
		os.system('sh ./src/client/cmds/email_confirmation.sh ' + sys.argv[1])
else:
	print "Invalid Argument Count"
