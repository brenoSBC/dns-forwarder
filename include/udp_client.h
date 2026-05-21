#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

void send_dns_query(int sockfd, const unsigned char *buffer, int buffer_size, const char *ip);

#endif