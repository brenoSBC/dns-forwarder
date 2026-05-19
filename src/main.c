#include "../include/header.h"
#include "../include/question.h"
#include "../include/query.h"

#include <stdio.h>
#include <string.h>

int main() {

    //testando apenas

    unsigned char header[12];
    unsigned char question[1024];
    unsigned char domain[] = "www.google.com";

    unsigned char query[1024];

    DNS_HEADER s_header = dns_header_init(123, 1, 1);

    int header_size = dns_header_serialize(header, s_header);

    DNS_QUESTION s_question = dns_question_init(1, 1);

    int question_size = dns_question_serialize(question, domain, s_question);

    dns_build_query(query, header, header_size, question, question_size);

    int query_size = header_size + question_size;

    printf("query size: %d", query_size);

    for (int i = 0; i < query_size; i++) {
        printf("header = 0b%08b\n");
    }
    return 0;
}