#include "../../../include/question.h"

DNS_QUESTION dns_question_deserialize(unsigned char *buffer) {

    DNS_QUESTION q = {0};

    int pos = 12;
    int domain_pos = 0;

    while(buffer[pos] != 0b00000000) {

        int label_size = buffer[pos++];

        for(int i = 0; i < label_size; i++) {
            q.qname[domain_pos++] = buffer[pos++];
        }
        q.qname[domain_pos++] = '.';
    }
    q.qname[domain_pos - 1] = '\0';
    pos++;

    q.qtype  = (buffer[pos] << 8) | buffer[pos+1];
    pos+=2;
    q.qclass = (buffer[pos] << 8) | buffer[pos+1];
    pos+=2;

    return q;
}

int dns_question_serialize(unsigned char *buffer, unsigned char *domain, DNS_QUESTION q) {

    int pos = 0;
    int label_len = 0;
    int label_pos = pos++;

    for(int i = 0; domain[i] != '\0'; i++) {
        if(domain[i] == '.') {
            buffer[label_pos] = label_len;
            label_len = 0;
            label_pos = pos++;
        } else {
            buffer[pos++] = domain[i];
            label_len++;
        }
    }
    buffer[label_pos] = label_len;
    buffer[pos++] = 0;

    buffer[pos++] = (q.qtype >> 8)  & 0b11111111;
    buffer[pos++] = (q.qtype)       & 0b11111111;

    buffer[pos++] = (q.qclass >> 8) & 0b11111111;
    buffer[pos++] = (q.qclass)      & 0b11111111;

    int buffer_size = pos;
    
    return buffer_size;
}