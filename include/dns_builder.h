#ifndef DNS_BUILDER_H
#define DNS_BUILDER_H

#include <stdio.h>
#include <inttypes.h>


typedef struct {

    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;

} DNS_HEADER;

/* DNS Header */


// flags
// QR      0b0                  // 1 bit
// OPCODE  0b0000               // 4 bits
// AA      0b0                  // 1 bit
// TC      0b0                  // 1 bit
// RD      0b1                  // 1 bit

// RA      0b0                  // 1 bit
// Z       0b000                // 3 bits
// RCODE   0b0000               // 4 bits

#define QR     0b1
#define OPCODE 0b0
#define AA     0b0
#define TC     0b0
#define RD     0b1
#define RA     0b0
#define Z      0b0
#define RCODE  0b0


// 16 bits
#define QDCOUNT_HIGH 0b00000000      
#define QDCOUNT_LOW  0b00000001

// 16 bits
#define ANCOUNT_HIGH 0b00000000
#define ANCOUNT_LOW  0b00000000

// 16 bits
#define NSCOUNT_HIGH 0b00000000
#define NSCOUNT_LOW  0b00000000

// 16 bits
#define ARCOUNT_HIGH 0b00000000 
#define ARCOUNT_LOW  0b00000000


/* DNS Question */

#define QTYPE_HIGH 0b00000000
#define QTYPE_LOW  0b00000001

#define QCLASS_HIGH 0b00000000
#define QCLASS_LOW  0b00000001


/* Function Prototypes */

void build_dns_header(unsigned char *header);

void build_dns_question(unsigned char *qname, int *question_size, int *qname_size, unsigned char *domain);

void build_dns_message(unsigned char *message, const unsigned char *header, const unsigned char *question, int *message_pos, int question_size);

#endif