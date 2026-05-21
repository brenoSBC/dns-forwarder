#include "../include/header.h"
#include "../include/question.h"
#include "../include/query.h"

#include "../include/udp_server.h"
#include "../include/udp_client.h"

#include <stdio.h>
#include <string.h>

unsigned char *dns_servers[] = {
    "8.8.8.8",
    "1.1.1.1"
};


int main() {


    int sock_server = create_server_socket();

    bind_udp_socket(sock_server, "127.0.0.1");

    unsigned char query[1024];

    struct sockaddr_in client_addr;

    int received = recv_udp_packet(sock_server, query, sizeof(query), &client_addr);

    DNS_HEADER h = dns_header_deserialize(query);
    DNS_QUESTION q = dns_question_deserialize(query);

    dns_header_normalize(&h);

    unsigned char header[12];
    int header_size = dns_header_serialize(header, h);

    unsigned char question[1024];
    int question_size = dns_question_serialize(question, q.qname, q);

    int query_size = question_size + header_size;
    
    unsigned char new_query[512];
    dns_build_query(new_query, header, header_size, question, question_size);

   for (int i = 0; i < query_size; i++) {
        printf("query = 0b%08b\n", new_query[i]);
    }


    // printf("Recebi %d bytes\n",received);
    // printf("\nQuestion: %s", q.qname);

    int sock_client = create_client_socket();

    int query_size_a = header_size + question_size;
    send_dns_query(sock_client, new_query, query_size_a, "8.8.8.8");

    unsigned char answer[512];
    int recv_b = recv_dns_answer(sock_client, answer);

    printf("RECEBI do servidor publico: %d", recv_b);
 








    
     //testando apenas

    // unsigned char header[12];
    // unsigned char question[1024];
    // unsigned char domain[] = "www.google.com";

    // unsigned char query[1024];

    // DNS_HEADER s_header = dns_header_init(123, 1, 1);

    // int header_size = dns_header_serialize(header, s_header);

    // DNS_QUESTION s_question = dns_question_init(1, 1);

    // int question_size = dns_question_serialize(question, domain, s_question);

    // dns_build_query(query, header, header_size, question, question_size);

    // int query_size = header_size + question_size;

    // printf("query size: %d", query_size);

    // for (int i = 0; i < query_size; i++) {
    //     printf("header = 0b%08b\n");
    // }

    return 0;
}