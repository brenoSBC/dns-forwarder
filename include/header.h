#ifndef HEADER_H
#define HEADER_H

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

DNS_HEADER dns_header_deserialize(unsigned char *buffer);

int dns_header_serialize(unsigned char *buffer, DNS_HEADER h);

void dns_header_normalize(DNS_HEADER *h);

#endif