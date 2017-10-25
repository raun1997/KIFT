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

#include "kift.h"

static ps_decoder_t *g_ps;
static cmd_ln_t *g_config;
static t_utt_states g_utt_state = UTT_STATE_WAITING;

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in*)sa)->sin_addr);
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static int read_data(int16 *buf, int num_samples, int socket)
{
	char *buf_pointer = (char*)buf;
	int num_bytes = num_samples * sizeof(int16);
	int rc;

  //printf("num_bytes : %d\n", num_bytes);
	while(num_bytes)
	{
		rc = recv(socket, buf_pointer, num_bytes, 0);
    //printf("%s", buf_pointer);
  //  printf("recieve : %d\n", rc);
    if (rc < 0)
    {
		//	printf("negative\n");
      return (rc);
    }
		if (rc > 0)
		{
			num_bytes -= rc;
			buf_pointer += rc;
  //    printf("positive\n");
			continue ;
		}
		return (0);
	}
//  printf("samples\n");
	return (num_samples);
}

static int read_samples(ps_decoder_t *g_ps, int num_samples, int socket)
{
	int16 client_message[BUF_SIZE];
	int rc;

	while (num_samples)
	{
		rc = read_data(client_message,
			(num_samples > BUF_SIZE) ? BUF_SIZE : num_samples, socket);
    if (rc > 0)
		{
			uint8 in_speech = 0;
			ps_process_raw(g_ps, client_message, rc, FALSE, FALSE);
      in_speech = ps_get_in_speech(g_ps);
      if (in_speech && (g_utt_state == UTT_STATE_WAITING))
      {
        g_utt_state = UTT_STATE_LISTENING;
        printf("Listening... %hhu\n", in_speech);
      }
      //printf("%d\n", in_speech);
      if (!in_speech && (g_utt_state == UTT_STATE_LISTENING))
      {
        g_utt_state = UTT_STATE_FINISHED;
      }
			num_samples -= rc;
		}
		else
			return (rc);
	}
	return (1);
}

int go(int read_size, int num_samples, int new_fd)
{
	int rc;

	do
	{
		read_size = 0;
		rc = recv(new_fd, &num_samples, sizeof(num_samples), 0);
		if (rc <= 0)
		{
			printf("Error or disconnected (%d) errno = %d\n", rc, errno);
			g_utt_state = UTT_STATE_ERROR;
			break ;
		}
		if (num_samples)
		{
			read_size = read_samples(g_ps, num_samples, new_fd);
			if (read_size != 1)
			{
				printf("Error reading samples: %d\n", read_size);
				g_utt_state = UTT_STATE_ERROR;
			}
		}
	} while(g_utt_state != UTT_STATE_FINISHED);
	return (0);
}

int set(int rv, int read_size, int new_fd, const char *hyp, int score)
{
	while(g_utt_state < UTT_STATE_QUIT) /* Internal loop processes individual requests from client */
	{
    /* TODO : GET THIS SHIT WORKING
    * ps_set_keyphrase(g_ps, "keyphrase_search", "sabre");
    * ps_set_search(g_ps, "keyphrase_search");
    */
		rv = ps_start_utt(g_ps);
		g_utt_state = UTT_STATE_WAITING;
		int32 num_samples = 0;
		go(read_size, num_samples, new_fd);
		if (g_utt_state == UTT_STATE_FINISHED)
		{
			rv = ps_end_utt(g_ps);
			hyp = ps_get_hyp(g_ps, &score);
			printf("Recognized: %s\n", hyp);
			if (hyp)
				send(new_fd , hyp, strlen(hyp), 0);
			if (hyp && strstr(hyp, "SHUTDOWN"))
				g_utt_state = UTT_STATE_QUIT;
			else
				g_utt_state = UTT_STATE_WAITING;
		}
		else
		{
			printf("Terminating connection due to error.\n");
			break ;
		}
	}
	return (0);
}

int ready(int rv, int read_size, int new_fd, const char *hyp, int score)
{
	if (!fork())
	{
		printf("Preparing to recieve ... \n");
		g_config = cmd_ln_init(NULL, ps_args(), TRUE,
							"-hmm", "./sabr/en-us-adapt",
							"-lm", "./sabr/model/sabr.lm",
							"-dict", "./sabr/model/sabr.dict",
							"-logfn", "kift.log",
							NULL);
	 if (g_config == NULL)
	 {
		 fprintf(stderr, "Failed to create g_config object, see log for details\n");
		 return (-1);
	 }
	 g_ps = ps_init(g_config);
	 if (g_ps == NULL)
	 {
		 fprintf(stderr, "Failed to create recognizer, see log for details\n");
		 return (-1);
	 }
	 set(rv, read_size, new_fd, hyp, score);
	 ps_free(g_ps);
	 cmd_ln_free_r(g_config);
	}
	return (0);
}

int process(int sockfd, socklen_t sin_size,
	struct sockaddr their_addr, char *s)
{
	int					new_fd;
	const char	*hyp;
	const char	*uttid;
	int					rv;
	int					score;
	int					read_size;

	read_size = 0;
  sin_size = sizeof(their_addr);
  new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
  if (new_fd < 0)
  {
    perror("accept");
    exit(1);
  }
  inet_ntop(their_addr.sa_family,
    get_in_addr((struct sockaddr *)&their_addr),
      s, sizeof(s));
	printf("server: got connection from %s\n", s);
	ready(rv, read_size, new_fd, hyp, score);
  close(new_fd);
  return (0);
}

int	main(int argc, char **argv)
{
  int sockfd;
  struct addrinfo hints, *servinfo;
  struct sockaddr their_addr;
	t_client_connection *con;
  socklen_t sin_size;
  int yes;
  char s[INET6_ADDRSTRLEN];
  int rv;
	int bytes;
	char	*ip;

	yes = 1;
  /* TODO : drop this shit into a function */
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
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
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
