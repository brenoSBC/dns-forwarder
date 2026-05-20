#ifndef QUESTION_H
#define QUESTION_H

#include <inttypes.h>

typedef struct {
    char qname[512];
    uint16_t qclass;
    uint16_t qtype;
} DNS_QUESTION;

DNS_QUESTION dns_question_deserialize(unsigned char *buffer);

DNS_QUESTION dns_question_init(uint16_t qclass, uint16_t qtype);

int dns_question_serialize(unsigned char *question, unsigned char *domain, DNS_QUESTION s_question);

#endif