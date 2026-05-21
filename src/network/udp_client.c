#include "../../include/udp_client.h"

int create_client_socket() {

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void send_dns_query(int sockfd, const unsigned char *buffer, int buffer_size, char *ip) {

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(SERVER_PORT);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    int send_bytes = sendto(sockfd, buffer, buffer_size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if(send_bytes < 0) {
        perror("sendto");
        exit (EXIT_FAILURE);
    }
}

int recv_dns_answer(int sockfd, unsigned char *buffer) {

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    socklen_t server_len = sizeof(server_addr);

    int recv_bytes = recvfrom(sockfd, buffer, BUFFSIZE, 0, (struct sockaddr *)&server_addr, &server_len);

    if(recv_bytes < 0) {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    return recv_bytes;
}