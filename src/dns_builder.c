#include "../include/dns_builder.h"

void build_dns_header(unsigned char *header, DNS_HEADER s_header) {

    

    header[0] = (s_header.id >> 8)       & 0b11111111;
    header[1] = (s_header.id)            & 0b11111111; 

    header[2] = (s_header.flags);

    


    header[4] = (s_header.qdcount >> 8)  & 0b11111111;
    header[5] = (s_header.qdcount)       & 0b11111111;

    header[6] = (s_header.ancount >> 8)  & 0b11111111;
    header[7] = (s_header.ancount)       & 0b11111111;
    
    header[8] = (s_header.nscount >> 8)  & 0b11111111;
    header[9] = (s_header.nscount)       & 0b11111111;

    header[10] = (s_header.arcount >> 8) & 0b11111111;
    header[11] = (s_header.arcount)      & 0b11111111;
}
