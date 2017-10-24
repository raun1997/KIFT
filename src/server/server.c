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

typedef enum
{
	UTT_STATE_WAITING = 0,
	UTT_STATE_LISTENING,
	UTT_STATE_FINISHED,
	UTT_STATE_ERROR,
	UTT_STATE_MAX,
	UTT_STATE_QUIT
} t_utt_states;

static ps_decoder_t *g_ps;
static cmd_ln_t *g_config;
static t_utt_states g_utt_state = UTT_STATE_WAITING;

/*
void sigchld_handler(int s)
{
    waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    int this = s;
    this = 0;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}*/



/*
int  process(char *file)
{
  ps_decoder_t *ps;
  cmd_ln_t *config;
  FILE *fh;
  char const *hyp, *uttid;
  int16 buf[512];
  int rv;
  int32 score;

  config = cmd_ln_init(NULL, ps_args(), TRUE,
		         "-hmm", MODELDIR "/en-us/en-us",
		         "-lm", MODELDIR "/en-us/en-us.lm.bin",
             "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
		         NULL);
  if (config == NULL)
  {
    fprintf(stderr, "Failed to create config object, see log for details\n");
	  return (-1);
  }
  ps = ps_init(config);
  if (ps == NULL)
  {
	  fprintf(stderr, "Failed to create recognizer, see log for details\n");
	  return (-1);
  }
  fh = fopen(file, "rb");
  if (fh == NULL)
  {
	  fprintf(stderr, "Unable to open input file.raw\n");
	  return (-1);
  }
  rv = ps_start_utt(ps);
  while (!feof(fh))
  {
    size_t nsamp;
	  nsamp = fread(buf, 2, 512, fh);
	  rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
  }
  rv = ps_end_utt(ps);
  hyp = ps_get_hyp(ps, &score);
  printf("Recognized: %s\n", hyp);
  fclose(fh);
  ps_free(ps);
  cmd_ln_free_r(config);
  return (0);
}
*/

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in*)sa)->sin_addr);
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void write_little_endian(unsigned int word, int num_bytes, FILE *wav_file)
{
  unsigned buf;

  while(num_bytes>0)
  {
    buf = word & 0xff;
    fwrite(&buf, 1,1, wav_file);
    num_bytes--;
    word >>= 8;
  }
}

/*
void write_wav(char *filename, unsigned long num_samples, int16 *data, int s_rate)
{
    FILE *wav_file;
    unsigned int sample_rate;
    unsigned int num_channels;
    unsigned int bytes_per_sample;
    unsigned int byte_rate;
    unsigned long i;

    printf("Writing to file ... \n");
    num_channels = 1;
    bytes_per_sample = 2;
    if (s_rate <= 0)
      sample_rate = 44100;
    else
      sample_rate = (unsigned int)s_rate;
    byte_rate = sample_rate * num_channels * bytes_per_sample;
    wav_file = fopen(filename, "w");
    assert(wav_file);
    printf("Writing ... \n");
    fwrite("RIFF", 1, 4, wav_file);
    write_little_endian(36 + bytes_per_sample * num_samples * num_channels, 4, wav_file);
    fwrite("WAVE", 1, 4, wav_file);
    printf("Before little endian ... ");
    fwrite("fmt ", 1, 4, wav_file);
    write_little_endian(16, 4, wav_file);
    write_little_endian(1, 2, wav_file);
    write_little_endian(num_channels, 2, wav_file);
    write_little_endian(sample_rate, 4, wav_file);
    write_little_endian(byte_rate, 4, wav_file);
    write_little_endian(num_channels * bytes_per_sample, 2, wav_file);
    write_little_endian(16 * bytes_per_sample, 2, wav_file);
    printf("After little endian ... ");
    fwrite("data", 1, 4, wav_file);
    write_little_endian(bytes_per_sample* num_samples * num_channels, 4, wav_file);
    i = -1;
    while (++i < num_samples)
      write_little_endian((unsigned int)(data[i]), bytes_per_sample, wav_file);
    printf("server: file create successfully");
    fclose(wav_file);
}*/

static int read_data(int16 *buf, int num_samples, int socket)
{
	char *buf_pointer = (char*)buf;
	int num_bytes = num_samples * sizeof(int16);

	while(num_bytes)
	{
		int rc = recv(socket, buf_pointer, num_bytes, 0);
		if (rc < 0)
			return (rc);
		if (rc > 0)
		{
			num_bytes -= rc;
			buf_pointer += rc;
			continue ;
		}
		return (0);
	}
	return (num_samples);
}

static int read_samples(ps_decoder_t *g_ps, int num_samples, int socket)
{
	int16 client_message[BUF_SIZE];

  //printf("Preparing to read samples ... \n");
	while (num_samples)
	{
		int rc = read_data(client_message, (num_samples > BUF_SIZE) ? BUF_SIZE : num_samples, socket);
  //  printf("Read ... %d\n", rc);
    //write_wav("./src/server/audio.test.wav", (unsigned long)num_samples, client_message, S_RATE);
    printf("Processing waves ... \n");
    if (rc > 0 && (g_utt_state == UTT_STATE_WAITING))
		{
			uint8 in_speech = 0;
    //  printf("Wave fault 1\n");
			printf("%d\n", ps_process_raw(g_ps, client_message, rc, FALSE, FALSE));
    //  printf("Wave fault 2\n");
      in_speech = ps_get_in_speech(g_ps);
    //  printf("Wave fault 3\n");
      if (in_speech)
      {
        g_utt_state = UTT_STATE_LISTENING;
        printf("Listening...\n");
      }
      if (!in_speech)
      {
        g_utt_state = UTT_STATE_FINISHED;
        printf("Finished, processing...\n");
      }
    //  printf("Running tests ... "); //
			num_samples -= rc;
		}
		else
			return (rc);
	}
	return (1);
}

int   main(int argc, char **argv)
{
  int sockfd;  // listen on sock_fd, new connection on new_fd
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr their_addr; // connector's address information
  socklen_t sin_size;
  int yes=1;
  char s[INET6_ADDRSTRLEN];
  int rv;
  //char buffer[MAXDATASIZE];
	int bytes;
	char	*ip;
  ps_decoder_t *g_ps;

    /* TODO : drop this shit into a function */

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP
 	hints.ai_protocol = 0;
	ip = get_ip_str();
	printf("Server hosting on ip : %s\n", ip);
	if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }
	printf("rv(%d)\n", rv);
  p = servinfo;
  while (p != NULL)
  {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
    {
      perror("server: socket");
      p = p->ai_next;
      continue;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      perror("setsockopt");
      exit(1);
    }
    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
    {
      close(sockfd);
      perror("server: bind");
      p = p->ai_next;
      continue;
    }
    break;
  }
  printf("socket connection : %d\n", sockfd);
  freeaddrinfo(servinfo);
  if (p == NULL)
	{
    fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
  if (listen(sockfd, BACKLOG) == -1)
	{
    perror("listen");
		exit(1);
	}
  while (1)
  {
    int new_fd;

		/*ps_decoder_t *g_ps;
    cmd_ln_t *g_config;*/

		char const *hyp, *uttid;
    int rv;
    int score;
    pid_t pid;
    int read_size = 0;

    /* Internal loop while processing connections */

  	printf("socket connection : %d\n", sockfd);
    sin_size = sizeof(their_addr);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd < 0)
    {
      printf("new fd: (%d)\n", new_fd);
      perror("accept");
      exit(1);
    }
    inet_ntop(their_addr.sa_family,
      get_in_addr((struct sockaddr *)&their_addr),
        s, sizeof s);
    printf("server: got connection from %s\n", s);
    if (!fork())
    {
	      //close(sockfd);
	      printf("Preparing to recieve ... \n");
	      g_config = cmd_ln_init(NULL, ps_args(), TRUE,
	                "-hmm", MODELDIR "/en-us/en-us",
	                "-lm", "model/model.lm",
	                "-dict", "model/model.dict",
	                "-logfn", "kift.log",
	                NULL);

		   if (g_config == NULL) {
		       fprintf(stderr, "Failed to create g_config object, see log for details\n");
		       return -1;
		   }
			 printf("g_config validated\n");
		   g_ps = ps_init(g_config);
		   if (g_ps == NULL) {
		       fprintf(stderr, "Failed to create recognizer, see log for details\n");
		       return -1;
		   }
			 printf("g_ps validated\n");
		   while(g_utt_state < UTT_STATE_QUIT)
		   {
		     rv = ps_start_utt(g_ps);
		     g_utt_state = UTT_STATE_WAITING;
		     int32 num_samples = 0;
		     do
		     {
		       read_size = 0;
		       int rc = recv(new_fd, &num_samples, sizeof(num_samples), 0);
		       if (rc <= 0)
		       {
		         printf("Error or disconnected (%d) errno = %d\n", rc, errno);
		         g_utt_state = UTT_STATE_ERROR;
		         break;
		       }
		       printf("%d samples (rc = %d)\n", num_samples, rc);
		       if (num_samples)
		       {
		         read_size = read_samples(g_ps, num_samples, new_fd);
						 printf("read size : %d\n", read_size);
						 if (read_size != 1)
		         {
		           printf("Error reading samples: %d\n", read_size);
		           g_utt_state = UTT_STATE_ERROR;
		         }
		       }
		   	 } while(g_utt_state < UTT_STATE_FINISHED);
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
		     break;
		   }
	 }
	   ps_free(g_ps);
	   cmd_ln_free_r(g_config);
	        //else
	        //{
	        //  for (int q = 0; buffer[q]; q++) printf("%d\n", buffer[q]); /* Jus debuggin */
	        //  write_wav("src/server/audio/in.wav", BUF_SIZE, buffer, S_RATE); /* NOTE : specifically this */
	        //}

	    }
			close(new_fd);
    //printf("Processing wav... ");
    //if (process("src/client/audio/in.wav") <= 0)
    //  perror("process");
  }
  return (0);
}
