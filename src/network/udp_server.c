#include "../../include/udp_server.h"

int create_udp_socket() {

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    return sockfd;
}


int recv_query(int sockfd, unsigned char *query) {
    
}