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

void write_wav(char *filename, unsigned long num_samples, char *data, int s_rate)
{
    FILE *wav_file;
    unsigned int sample_rate;
    unsigned int num_channels;
    unsigned int bytes_per_sample;
    unsigned int byte_rate;
    unsigned long i;    /* counter for samples */

    printf("Writing to file ... \n");
    num_channels = 1;   /* monoaural */
    bytes_per_sample = 2;
    if (s_rate <= 0)
      sample_rate = 44100;
    else
      sample_rate = (unsigned int)s_rate;
    byte_rate = sample_rate * num_channels * bytes_per_sample;
    wav_file = fopen(filename, "w");
    assert(wav_file);   /* make sure it opened */
    printf("Writing ... \n");
    fwrite("RIFF", 1, 4, wav_file);
    write_little_endian(36 + bytes_per_sample * num_samples * num_channels, 4, wav_file);
    fwrite("WAVE", 1, 4, wav_file);

    /* write fmt  subchunk */

    fwrite("fmt ", 1, 4, wav_file);
    write_little_endian(16, 4, wav_file);   /* SubChunk1Size is 16 */
    write_little_endian(1, 2, wav_file);    /* PCM is format 1 */
    write_little_endian(num_channels, 2, wav_file);
    write_little_endian(sample_rate, 4, wav_file);
    write_little_endian(byte_rate, 4, wav_file);
    write_little_endian(num_channels * bytes_per_sample, 2, wav_file);  /* block align */
    write_little_endian(16 * bytes_per_sample, 2, wav_file);  /* bits/sample */

    /* write data subchunk */
    fwrite("data", 1, 4, wav_file);
    write_little_endian(bytes_per_sample* num_samples * num_channels, 4, wav_file);
    i = -1;
    while (++i < num_samples)
      write_little_endian((unsigned int)(data[i]), bytes_per_sample, wav_file);
    printf("server: file create successfully");
    fclose(wav_file);
}

int   main(int argc, char **argv)
{
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr; // connector's address information
  socklen_t sin_size;
  int yes=1;
  char s[INET6_ADDRSTRLEN];
  int rv;
  char buffer[MAXDATASIZE];
	int bytes;
	char	*ip;

    /* TODO : drop this shit into a function */

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP
	ip = get_ip_str();
    if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0)
    {
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
    printf("server: waiting for connections...\n");
  while (1)
  {

    /* Internal loop while processing connections */

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
    //char *audio = strdup(strcat(AUDIO_PATH, "input.raw"));
    //printf("%s\n", audio);
    if (!fork())
    {
      close(sockfd);

        /* I'm not sure this is the way to go */
      if ((bytes = recv(new_fd, &buffer, 256, 0)) == -1)
        perror("client: recieve");
      else
      {
        for (int q = 0; buffer[q]; q++) printf("%d\n", buffer[q]); /* Jus debuggin */
        write_wav("src/server/audio/in.wav", BUF_SIZE, buffer, S_RATE); /* NOTE : specifically this */
      }
      close(new_fd);
    }
    printf("Processing wav... ");
    if (process("src/client/audio/in.wav") <= 0)
      perror("process");
  }
  return 0;
}
