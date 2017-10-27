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

void		*get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
  	return &(((struct sockaddr_in*)sa)->sin_addr);
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static void	find_socket(t_client_connection *con)
{
	int sockfd;

	while (con->p != NULL)
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

static void	get_servinfo(t_client_connection *con)
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
	con->p = servinfo;
	return ;
}

static int	init_connect(t_client_connection *con)
{
	char s[INET6_ADDRSTRLEN];

	get_servinfo(con);
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

int			main()
{
	t_client_connection	*con;

	con->pid = api_token_grab("src/client/cmds/json/42_api_token.json");
	system("electron ./ &");
	con = malloc(sizeof(t_client_connection));
	if (init_connect(con))
		return (-1);
	printf("Connected\n");
	recognize(con);
	close(con->sock);
	kill(con->pid, SIGTERM);
	sleep(5);
	if (waitpid(con->pid, NULL, WNOHANG) != con->pid)
		kill(con->pid, SIGKILL);
	if (con)
		free(con);
	return (0);
}
