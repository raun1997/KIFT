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
        while (1)
        {
          if ((rv = getaddrinfo(NULL, PORT, &k_addr, &servinfo)) != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
                return 1;
            }
            // loop through all the results and connect to the first we can
          for (p = servinfo; p != NULL; p = p->ai_next)
          {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {
              perror("client: socket");
              continue;
            }
            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
            {
              close(sockfd);
              perror("client: connect");
              continue;
            }
            break;
          }
          if (p == NULL)
          {
            fprintf(stderr, "client: failed to connect\n");
            return 2;
          }
          inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),s, sizeof s);
          printf("client: connecting to %s\n", s);
          freeaddrinfo(servinfo); // all done with this structure
          if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
              perror("recv");
            exit(1);
          }
          buf[numbytes] = '\0';
          printf("client: received '%s'\n",buf);
          close(sockfd);
        }
}
