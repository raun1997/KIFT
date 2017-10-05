/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:04 by scollet           #+#    #+#             */
/*   Updated: 2017/10/04 16:25:05 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/kift.h"

int   main(int ac, char **av)
{
  // TODO INITIALIZE SERVER
  int sockfd;
  struct sockaddr_in my_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0); // do some error checking!
  my_addr.sin_family = AF_INET;         // host byte order
  my_addr.sin_port = htons(PORT);     // short, network byte order
  my_addr.sin_addr.s_addr = inet_addr(IP);
  memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct
  // don't forget your error checking for bind():
  bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
  while (1)
  {
    // LISTEN ON SERVER FOR CONNECTIONS
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
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
  return 0;
}
