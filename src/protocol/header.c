#include "../../include/header.h"

DNS_HEADER dns_header_deserialize(unsigned char *buffer) {

    DNS_HEADER h = {0};

    h.id = (buffer[0] << 8) | buffer[1];

    h.flags.qr     = (buffer[2] >> 7) & 0b1;
    h.flags.opcode = (buffer[2] >> 3) & 0b1111;
    h.flags.aa     = (buffer[2] >> 2) & 0b1;
    h.flags.tc     = (buffer[2] >> 1) & 0b1;
    h.flags.rd     =  buffer[2]       & 0b1;

    h.flags.ra     = (buffer[3] >> 7) & 0b1;
    h.flags.z      = (buffer[3] >> 4) & 0b111;
    h.flags.rcode  =  buffer[3]       & 0b1111;

    h.qdcount = (buffer[4]  << 8) | buffer[5];
    h.ancount = (buffer[6]  << 8) | buffer[7];
    h.nscount = (buffer[8]  << 8) | buffer[9];
    h.arcount = (buffer[10] << 8) | buffer[11];

    return h;
}

int dns_header_serialize(unsigned char *buffer, DNS_HEADER h) {

    buffer[0] = (h.id >> 8)       & 0b11111111;
    buffer[1] = (h.id)            & 0b11111111; 

    buffer[2] = ((h.flags.qr     & 0b1)    << 7) |
                ((h.flags.opcode & 0b1111) << 3) |
                ((h.flags.aa     & 0b1)    << 2) |
                ((h.flags.tc     & 0b1)    << 1) |
                ((h.flags.rd     & 0b1)    << 0);

    buffer[3] = ((h.flags.ra    & 0b1)    << 7) |
                ((h.flags.z     & 0b111)  << 4) |
                ((h.flags.rcode & 0b1111));

    buffer[4] = (h.qdcount >> 8)  & 0b11111111;
    buffer[5] = (h.qdcount)       & 0b11111111;

    buffer[6] = (h.ancount >> 8)  & 0b11111111;
    buffer[7] = (h.ancount)       & 0b11111111;
    
    buffer[8] = (h.nscount >> 8)  & 0b11111111;
    buffer[9] = (h.nscount)       & 0b11111111;

    buffer[10] = (h.arcount >> 8) & 0b11111111;
    buffer[11] = (h.arcount)      & 0b11111111;

    return 12;
}

void dns_header_normalize(DNS_HEADER *h) {
    h->flags.qr     = 0;  
    h->flags.opcode = 0;  
    h->flags.z      = 0;  
    h->flags.rcode  = 0;  

    if(h->qdcount == 0) h->qdcount = 1;
    h->ancount = 0;
    h->nscount = 0;
    h->arcount = 0;
}



