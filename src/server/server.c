/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:25:04 by scollet           #+#    #+#             */
/*   Updated: 2017/10/27 01:16:25 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void		*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return (&(((struct sockaddr_in6*)sa)->sin6_addr));
}

int			process(int sockfd, socklen_t sin_size,
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

int			main(int ac, char **av)
{
	int					sockfd;
	struct addrinfo		hints;
	struct addrinfo		*servinfo;
	struct sockaddr		their_addr;
	t_client_connection	*con;
	socklen_t			sin_size;
	int					yes;
	char				s[INET6_ADDRSTRLEN];
	int					rv;
	char				*ip;

	yes = 1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	ip = get_ip_str();
	printf("Server hosting on ip : %s\n", ip);
	if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return (1);
	}
	printf("rv(%d)\n", rv);
	con->p = servinfo;
	while (con->p != NULL)
	{
		if ((sockfd = socket(con->p->ai_family, con->p->ai_socktype,
		con->p->ai_protocol)) == -1)
		{
			perror("server: socket");
			con->p = con->p->ai_next;
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
					&yes, sizeof(int)) == -1)
		{
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd, con->p->ai_addr, con->p->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("server: bind");
			con->p = con->p->ai_next;
			continue;
		}
		break ;
	}
	printf("socket connection : %d\n", sockfd);
	freeaddrinfo(servinfo);
	if (con->p == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}
	process(sockfd, sin_size, their_addr, s);
	return (0);
}
