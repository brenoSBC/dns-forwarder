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

int dns_header_serialize(unsigned char *header, DNS_HEADER s_header) {

    header[0] = (s_header.id >> 8)       & 0b11111111;
    header[1] = (s_header.id)            & 0b11111111; 

    header[2] = ((s_header.flags.qr     & 0b1)    << 7) |
                ((s_header.flags.opcode & 0b1111) << 3) |
                ((s_header.flags.aa     & 0b1)    << 2) |
                ((s_header.flags.tc     & 0b1)    << 1) |
                ((s_header.flags.rd     & 0b1)    << 0);

    header[3] = ((s_header.flags.ra    & 0b1)    << 7) |
                ((s_header.flags.z     & 0b111)  << 4) |
                ((s_header.flags.rcode & 0b1111));

    header[4] = (s_header.qdcount >> 8)  & 0b11111111;
    header[5] = (s_header.qdcount)       & 0b11111111;

    header[6] = (s_header.ancount >> 8)  & 0b11111111;
    header[7] = (s_header.ancount)       & 0b11111111;
    
    header[8] = (s_header.nscount >> 8)  & 0b11111111;
    header[9] = (s_header.nscount)       & 0b11111111;

    header[10] = (s_header.arcount >> 8) & 0b11111111;
    header[11] = (s_header.arcount)      & 0b11111111;

    return 12;
}

void dns_header_normalize(DNS_HEADER *h) {
    h->flags.qr     = 0;  
    h->flags.opcode = 0;  
    h->flags.z      = 0;  
    h->flags.rcode  = 0;  
    if(h->qdcount == 0) h->qdcount = 1;
}



