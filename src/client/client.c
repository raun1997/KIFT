/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:11 by scollet           #+#    #+#             */
/*   Updated: 2017/10/27 15:29:13 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "kift.h"

void		*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return (&(((struct sockaddr_in6*)sa)->sin6_addr));
}

int			get_in(t_client_connection *con, int sockfd)
{
	if ((sockfd = socket(con->p->ai_family,
		con->p->ai_socktype, con->p->ai_protocol)) == -1)
	{
		perror("client: socket");
		con->p = con->p->ai_next;
	}
	con->sock = sockfd;
	if (connect(sockfd, con->p->ai_addr, con->p->ai_addrlen) == -1)
	{
		close(sockfd);
		perror("client: connect");
		con->p = con->p->ai_next;
	}
	printf("Client socket : %d\n", sockfd);
	if (con->p == NULL)
	{
		fprintf(stderr, "client: failed to connect\n");
		return (-1);
	}
	return (0);
}

static int	init_connect(t_client_connection *con, int rv)
{
	int				sockfd;
	char			*ip;
	char			s[INET6_ADDRSTRLEN];

	con->hints.ai_family = AF_UNSPEC;
	con->hints.ai_socktype = SOCK_STREAM;
	con->hints.ai_protocol = 0;
	ip = get_ip_str();
	if ((rv = getaddrinfo(ip, PORT, &con->hints, &con->servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return (1);
	}
	con->p = con->servinfo;
	if (get_in(con, sockfd) < 0)
		return (-1);
	inet_ntop(con->p->ai_family,
		get_in_addr((struct sockaddr *)con->p->ai_addr), s, sizeof(s));
	printf("client: connecting to %s\n", s);
	freeaddrinfo(con->servinfo);
	return (0);
}

int			main(int argc, char **argv)
{
	t_client_connection	*con;
	int					rv;

	srand(time(NULL));
	if (access("logs.log", F_OK) != -1)
		system("rm logs.log");
	con = malloc(sizeof(t_client_connection));
	if (init_connect(con, rv))
		return (-1);
	printf("Connected\n");
	system("electron . &");
	recognize(con);
	close(con->sock);
	if (con)
		free(con);
	system("killall Electron 2>/dev/null");
	return (0);
}
