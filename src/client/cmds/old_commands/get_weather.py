# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    get_weather.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/20 16:49:04 by etregoni          #+#    #+#              #
#    Updated: 2017/10/20 16:49:06 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pyowm

owm = pyowm.OWM('8c1b88f5ffc94dc1c4ce9d94b4520325')

#orecast = owm.hourly_forecast("Milan,it")
#tomorrow = pyowm.timeutils.tomorrow()
#forecast.will_be_sunny_at(tomorrow)  # Always True in Italy, right? ;-)

# Search for current weather
observation = owm.weather_at_place('37.5497,-121.9621')
w = observation.get_weather()
print(w)

# Weather details
w.get_wind()                  # {'speed': 4.6, 'deg': 330}
w.get_humidity()              # 87
w.get_temperature('celsius')  # {'temp_max': 10.5, 'temp': 9.7, 'temp_min': 9.0}
print(w.get_wind())
print(w.get_humidity())
print(w.get_temperature('fahrenheit'))
# Search current weather observations in the surroundings of
# lat=22.57W, lon=43.12S (Rio de Janeiro, BR)
observation_list = owm.weather_around_coords(-22.57, -43.12)
