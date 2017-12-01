/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:04 by scollet           #+#    #+#             */
/*   Updated: 2017/10/27 15:05:25 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return (&(((struct sockaddr_in6*)sa)->sin6_addr));
}

int		process(int sockfd, socklen_t sin_size,
	struct sockaddr their_addr, char *s)
{
	Package		*pack;
	const char	*uttid;

	pack = (Package*)malloc(sizeof(Package));
	pack->read_size = 0;
	sin_size = sizeof(their_addr);
	pack->new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	if (pack->new_fd < 0)
	{
		perror("accept");
		exit(1);
	}
	inet_ntop(their_addr.sa_family,
		get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof(s));
	printf("server: got connection from %s\n", s);
	ready(pack);
	close(pack->new_fd);
	return (0);
}

int		get_in(t_client_connection *con)
{
	int sockfd;
	int yes;

	yes = 1;
	if ((sockfd = socket(con->p->ai_family, con->p->ai_socktype,
	con->p->ai_protocol)) == -1)
	{
		perror("server: socket");
		exit(1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
				&yes, sizeof(int)) == -1 ||
	bind(sockfd, con->p->ai_addr, con->p->ai_addrlen) == -1)
	{
		close(sockfd);
		perror("server");
		exit(1);
	}
	freeaddrinfo(con->servinfo);
	if (con->p == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
	return (sockfd);
}

char	*pull_ip(void)
{
	char *ip;

	ip = get_ip_str();
	printf("Server hosting on ip : %s\n", ip);
	return (ip);
}

int		main(int ac, char **av)
{
	int					sockfd;
	t_client_connection	*con;
	socklen_t			sin_size;
	char				s[INET6_ADDRSTRLEN];
	int					rv;

	con = (t_client_connection*)malloc(sizeof(t_client_connection));
	con->hints.ai_family = AF_UNSPEC;
	con->hints.ai_socktype = SOCK_STREAM;
	con->hints.ai_flags = AI_PASSIVE;
	con->hints.ai_protocol = 0;
	if ((rv = getaddrinfo(pull_ip(), PORT, &con->hints, &con->servinfo)) != 0 &&
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv)) != -1)
		return (1);
	con->p = con->servinfo;
	if (listen(sockfd = get_in(con), BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}
	process(sockfd, sin_size, con->their_addr, s);
	return (0);
}
