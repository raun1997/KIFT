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
#include <pocketsphinx.h>
#include <assert.h>

#define S_RATE (44100)
#define BUF_SIZE (S_RATE * 2)

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

void  process(char *file)
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
	  return -1;
  }
  ps = ps_init(config);
  if (ps == NULL)
  {
	  fprintf(stderr, "Failed to create recognizer, see log for details\n");
	  return -1;
  }
  fh = fopen(file, "rb");
  if (fh == NULL)
  {
	  fprintf(stderr, "Unable to open input file goforward.raw\n");
	  return -1;
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
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void write_little_endian(unsigned int word, int num_bytes, FILE *wav_file)
{
    unsigned buf;
    while(num_bytes>0)
    {   buf = word & 0xff;
        fwrite(&buf, 1,1, wav_file);
        num_bytes--;
    word >>= 8;
    }
}

void write_wav(char *filename, unsigned long num_samples, char *data, int s_rate)
{
    FILE *wav_file;
    unsigned int sample_rate;
    unsigned int num_channels;
    unsigned int bytes_per_sample;
    unsigned int byte_rate;
    unsigned long i;    /* counter for samples */

    num_channels = 1;   /* monoaural */
    bytes_per_sample = 2;
    if (s_rate<=0)
      sample_rate = 44100;
    else
      sample_rate = (unsigned int)s_rate;
    byte_rate = sample_rate * num_channels * bytes_per_sample;
    wav_file = fopen(filename, "w");
    assert(wav_file);   /* make sure it opened */
    fwrite("RIFF", 1, 4, wav_file);
    write_little_endian(36 + bytes_per_sample* num_samples*num_channels, 4, wav_file);
    fwrite("WAVE", 1, 4, wav_file);
    /* write fmt  subchunk */
    fwrite("fmt ", 1, 4, wav_file);
    write_little_endian(16, 4, wav_file);   /* SubChunk1Size is 16 */
    write_little_endian(1, 2, wav_file);    /* PCM is format 1 */
    write_little_endian(num_channels, 2, wav_file);
    write_little_endian(sample_rate, 4, wav_file);
    write_little_endian(byte_rate, 4, wav_file);
    write_little_endian(num_channels * bytes_per_sample, 2, wav_file);  /* block align */
    write_little_endian(8*bytes_per_sample, 2, wav_file);  /* bits/sample */

    /* write data subchunk */
    fwrite("data", 1, 4, wav_file);
    write_little_endian(bytes_per_sample* num_samples*num_channels, 4, wav_file);
    i = -1;
    while (++i < num_samples)
      write_little_endian((unsigned int)(data[i]),bytes_per_sample, wav_file);
    printf("server: file create successfully");
    fclose(wav_file);
}

int   main(int argc, char **argv)
{
//  FILE* wav_file;
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
//    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
//    ps_decoder_t *ps = NULL;
//    cmd_ln_t *config = NULL;
    char buffer[MAXDATASIZE];
//	float t;
	int bytes;

/*    config = cmd_ln_init(NULL, ps_args(), TRUE,
		         "-hmm", MODELDIR "/en-us/en-us",
	                 "-lm", MODELDIR "/en-us/en-us.lm.bin",
	                 "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
	                 NULL);*/
  if (argc == 1)
  {
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(av[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
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
    freeaddrinfo(servinfo);
    if (p == NULL)
      fprintf(stderr, "server: failed to bind\n"), exit(1);
    if (listen(sockfd, BACKLOG) == -1)
      perror("listen"), exit(1);
    /*sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
      perror("sigaction");
      exit(1);
    }*/
    printf("server: waiting for connections...\n");
    while (1)
    {
      sin_size = sizeof their_addr;
      new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
      if (new_fd == -1)
      {
        perror("accept");
        continue;
      }
      inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
          s, sizeof s);
      printf("server: got connection from %s\n", s);
      if (!fork())
      {
        close(sockfd);
        if ((bytes = recv(new_fd, &buffer, MAXDATASIZE - 1, 0)) == -1)
          perror("client: recieved");
        else
          write_wav("input.wav", BUF_SIZE, buffer, S_RATE);
        close(new_fd);
        exit(0);
      }
      close(new_fd);
      process("input.wav");
    }
  }
  else
    perror("usage: ./server <host.ip.address> || ");
  return 0;
}
