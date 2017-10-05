/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:11 by scollet           #+#    #+#             */
/*   Updated: 2017/10/04 16:25:13 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int ac, char **av)
{
  // INITIALIZE CLIENT
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  // QUERY SERVER
  // c = connect(int socket, const struct sockaddr *address, socklen_t address_len)
  // loop
    // IF c is > 0
      // while program is not terminated
        // wait for keyword
        // msg = record message();
        // send(msg);
    // ELSE
      // retry NUM_TRIES;
      // if retries exceed limit
        // ping error("UNABLE TO CONNECT");
        // exit();
}
