/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:11 by scollet           #+#    #+#             */
/*   Updated: 2017/10/07 14:04:41 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
  	return &(((struct sockaddr_in*)sa)->sin_addr);
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static void				find_socket(t_client_connection *con)
{
	int sockfd;

	while (con->p != NULL) /* CYCLE THROUGH STUFF */
	{
		if ((sockfd = socket(con->p->ai_family, con->p->ai_socktype,
				con->p->ai_protocol)) == -1)
		{
			perror("client: socket");
			con->p = con->p->ai_next;
			continue;
		}
		con->sock = sockfd;
		if (connect(sockfd, con->p->ai_addr, con->p->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("client: connect");
			con->p = con->p->ai_next;
			continue;
		}
		printf("Client socket : %d\n", sockfd);
		break ;
	}
}

static struct addrinfo		*get_servinfo(t_client_connection *con)
{
	struct addrinfo hints;
	struct addrinfo *servinfo;
	char *ip;
	int rv;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	ip = get_ip_str();
	if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(-1);
	}
	return (servinfo);
}

static int				init_connect(t_client_connection *con)
{
	char s[INET6_ADDRSTRLEN];

	con->p = get_servinfo(con);
	find_socket(con);
	if (con->p == NULL)
	{
		fprintf(stderr, "client: failed to connect\n");
		return (-1);
	}
	inet_ntop(con->p->ai_family,
			get_in_addr((struct sockaddr *)con->p->ai_addr), s, sizeof s);
	printf("client: connecting to %s\n", s);
	freeaddrinfo(con->p);
	return (0);
}

int main(int argc, char **argv)
{
	t_client_connection	*con;

	con = malloc(sizeof(t_client_connection));
		if (init_connect(con))
		return (-1);
	printf("Connected\n");
	recognize(con);
	close(con->sock);
		if (con) free(con);
	return (0);
}

  // int	sockfd, numbytes;
  // char	*output;
  // struct 	addrinfo hints, *servinfo, *p;
  // int 	rv;
  // char 	s[INET6_ADDRSTRLEN];
  // char	*ip;
  //
  // /* Client takes IP address of machine as an argument */
  //
	// //if (argc == 1)
	// //{
  //
  // /* TODO : drop this shit into a function */
  //
	// memset(&hints, 0, sizeof hints);
  // hints.ai_family = AF_UNSPEC;
 // 	hints.ai_socktype = SOCK_STREAM;
  // hints.ai_protocol = 0;
	// ip = get_ip_str();
  // if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
	// {
  //   fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
  //   return 1;
  // }
  // p = servinfo;
  // while (p != NULL) /* CYCLE THROUGH STUFF */
  // {
  //   if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
  //   {
  //     perror("client: socket");
  //     p = p->ai_next;
  //     continue;
  //   }
  //   if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
  //   {
  //     close(sockfd);
  //     perror("client: connect");
  //     p = p->ai_next;
  //     continue;
  //   }
  //   printf("Client socket : %d\n", sockfd);
  //   break;
  // }
  // if (p == NULL)
  // {
  //   fprintf(stderr, "client: failed to connect\n");
  //   return (2);
  // }
  // inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
  // printf("client: connecting to %s\n", s);
  // freeaddrinfo(servinfo);
  //
  // /* TODO : drop this shit into a function */
  //
  // int u = 1;
  // while (u)
  // {
  //
  //   /* Internal loop while recording user */
  //   /* TODO : activate recording function on some input instead of attempting to record continuously */
  //   /* NOTE : Using external input we can let the user decide when to activate, just not sure how ... */
  //
  //   record();
  //   printf("Finished recording ... \n");
  //   //printf();
  //   if ((numbytes = send(sockfd, "./src/client/audio/test4.wav", MAXDATASIZE - 1, 0)) == -1)
  //   {
  //     perror("send");
  //    	exit(1);
  //   }
  //   printf("number of bytes sent : %d\n", numbytes);
  //   printf("client: sent file successfully\n");
  //   close(sockfd);
  //   u = !u;
  // }
  // return 0;
// }
