#include "../../include/udp_server.h"

int create_server_socket() {

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void bind_udp_socket(int sockfd, const char *ip) {

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int bind_result = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if(bind_result < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}

int recv_udp_packet(int sockfd, unsigned char *buffer, int buffer_size, struct sockaddr_in *client_addr) {
    
    socklen_t client_len = sizeof(*client_addr);

    int recv = recvfrom(sockfd, buffer, buffer_size, 0, (struct sockaddr *)client_addr, &client_len);

    if(recv < 0) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }
    return recv;
}