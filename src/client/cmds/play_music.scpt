-- **************************************************************************** --
--                                                                              --
--                                                         :::      ::::::::    --
--    play_music.scpt                                    :+:      :+:    :+:    --
--                                                     +:+ +:+         +:+      --
--    By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+         --
--                                                 +#+#+#+#+#+   +#+            --
--    Created: 2017/10/27 06:45:34 by etregoni          #+#    #+#              --
--    Updated: 2017/10/27 06:45:36 by etregoni         ###   ########.fr        --
--                                                                              --
-- **************************************************************************** --

set audioPath to "src/client/audio/"
set playList to {"bonnie.mp3", "karr.mp3", "long_walk.mp3", "pipes.mp3", "self_control.mp3", "tony.mp3"}
set listSize to count of playList
set randNum to (random number from 1 to listSize)
set randSong to item randNum of playList
set song to audioPath & randSong
do shell script "afplay " & song
