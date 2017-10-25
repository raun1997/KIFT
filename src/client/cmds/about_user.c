/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_user.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:10:58 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/24 15:11:01 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void user_name(void)
{
	//robot introduces itself and asks user for name, then stores name in a file
	//this function will call that file with flite or say to reply with users' name
}

void user_loc(void)
{
	ip_info();
	//call flite_transcripts/location with say or flite to say location


}

void check_history(void) {
	// as commands are given, they will be appended to a file,
	// this function will either cat that file in terminal or open in textedit
}
