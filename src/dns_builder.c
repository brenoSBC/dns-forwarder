#include "../include/dns_builder.h"

DNS_HEADER dns_header_init(uint16_t id, uint8_t rd, uint16_t qdcount) {

    DNS_HEADER s_header = {0};

    s_header.id           = id;
    s_header.flags.qr     = 0;  
    s_header.flags.opcode = 0;  
    s_header.flags.aa     = 0;  
    s_header.flags.tc     = 0;
    s_header.flags.rd     = rd;      // normalmente 1
    s_header.flags.ra     = 0;  
    s_header.flags.z      = 0;  
    s_header.flags.rcode  = 0;  
    s_header.qdcount      = qdcount; // normalmente 1
    s_header.ancount      = 0;       
    s_header.nscount      = 0;
    s_header.arcount      = 0;

    return s_header;
}

void dns_header_serialize(unsigned char *header, DNS_HEADER s_header) {

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
}

DNS_QUESTION dns_question_init(uint16_t qclass, uint16_t qtype) {

    DNS_QUESTION s_question = {0};
    
    s_question.qclass = qclass; // normalmente 1
    s_question.qtype  = qtype;  // normalmente 1

    return s_question;
}

void dns_question_serialize(unsigned char *question, unsigned char *domain, DNS_QUESTION s_question) {

    int pos = 0;
    int label_len = 0;
    int label_pos = pos++;

    for(int i = 0; domain[i] != '\0'; i++) {
        if(domain[i] == '.') {
            question[label_pos] = label_len;
            label_len = 0;
            label_pos = pos++;
        } else {
            question[pos++] = domain[i];
            label_len++;
        }
    }
    question[label_pos] = label_len;
    question[pos++] = 0;

    question[pos++] = (s_question.qclass >> 8) & 0b11111111;
    question[pos++] = (s_question.qclass)      & 0b11111111;

    question[pos++] = (s_question.qtype >> 8)  & 0b11111111;
    question[pos++] = (s_question.qtype)       & 0b11111111;
}

