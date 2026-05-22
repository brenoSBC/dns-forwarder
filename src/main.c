#include "../include/header.h"
#include "../include/question.h"
#include "../include/query.h"

#include "../include/udp_server.h"
#include "../include/udp_client.h"

#include <stdio.h>
#include <string.h>

#define LOCALHOST "127.0.0.1"

int main() {

    while(1) {
    unsigned char header   [12];
    unsigned char question [1024];
    unsigned char org_query[1024];
    unsigned char new_query[1024];
    unsigned char answer   [1024];

    int server_sockfd;
    int client_sockfd;
    int recv_org_packet;  
    int recv_new_packet;  
    int header_size;
    int question_size;
    int query_size;

    DNS_HEADER h;
    DNS_QUESTION q;
    
    struct sockaddr_in client_addr;
    
    /* Create Sockets */
    server_sockfd = create_server_socket();
    client_sockfd = create_client_socket();

    /* Binding on 127.0.0.1 */
    bind_udp_socket(server_sockfd, LOCALHOST);

    /* Recv query already done from operational system */
    recv_org_packet = recv_udp_packet(server_sockfd, org_query, sizeof(org_query), &client_addr);

    /* Deserialize query from operational system */
    h = dns_header_deserialize(org_query);
    dns_header_normalize(&h);
    q = dns_question_deserialize(org_query);

    /* Serialize Header, Question and make Query */
    header_size = dns_header_serialize(header, h);
    question_size = dns_question_serialize(question, q.qname, q);
    dns_build_query(new_query, header, header_size, question, question_size);

    /* Send the New Query to the public DNS server */
    query_size = header_size + question_size;
    send_dns_query(client_sockfd, new_query, query_size, "8.8.8.8");

    /* Recv the Answer from the public DNS server */
    recv_new_packet = recv_dns_answer(client_sockfd, answer);

    send_udp_packet(server_sockfd, answer, recv_new_packet, &client_addr);

    /* Close server and client sockets */
    close(server_sockfd);
    close(client_sockfd);

    }

    return 0;
}

    // for (int i = 0; i < query_size; i++) {
    //     printf("query = 0b%08b\n", new_query[i]);
    // }


    // printf("Recebi do sistema operacional %d bytes\n",recv_org_packet);
    // printf("\nQuestion: %s", q.qname);

    //  printf("RECEBI do servidor publico: %d", recv_new_packet);