#ifndef DNS_BUILDER_H
#define DNS_BUILDER_H

#include <stdio.h>
#include <inttypes.h>

typedef struct {
    uint8_t qr;
    uint8_t opcode;
    uint8_t aa;
    uint8_t tc;
    uint8_t rd;
    uint8_t ra;
    uint8_t z;
    uint8_t rcode;
} DNS_HEADER_FLAGS;

typedef struct {
    uint16_t id;
    DNS_HEADER_FLAGS flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} DNS_HEADER;

typedef struct {
    uint16_t qclass;
    uint16_t qtype;
} DNS_QUESTION;



DNS_HEADER dns_header_init(uint16_t id, uint8_t rd, uint16_t qdcount);

void dns_header_serialize(unsigned char *header, DNS_HEADER s_header);

DNS_QUESTION dns_question_init(uint16_t qclass, uint16_t qtype);

void dns_question_serialize(unsigned char *question, unsigned char *domain, DNS_QUESTION s_question);

#endif