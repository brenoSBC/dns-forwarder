#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/time.h>
#include <errno.h>

#define PORT 53
#define BUFFSIZE 1024

void send_dns_query(int sockfd, const unsigned char *buffer, int buffer_size, const char *ip);

#endif