#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/time.h>
#include <errno.h>

#define PORT 8053

int create_server_socket();

void bind_udp_socket(int sockfd, const char *ip);

int recv_udp_packet(int sockfd, unsigned char *buffer, int buffer_size, struct sockaddr_in *client_addr);

#endif