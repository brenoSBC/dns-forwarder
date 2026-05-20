#include "../../include/question.h"

DNS_QUESTION dns_question_deserialize(unsigned char *buffer) {

    DNS_QUESTION q = {0};

    int pos = 12;
    int name_pos = 0;

    while(buffer[pos] != 0b00000000) {

        int label_size = buffer[pos++];

        for(int i = 0; i < label_size; i++) {
            q.qname[name_pos++] = buffer[pos++];
        }
        q.qname[name_pos++] = '.';
    }
    pos++;

    q.qtype  = (buffer[pos] << 8) | buffer[pos+1];
    pos+=2;
    q.qclass = (buffer[pos] << 8) | buffer[pos+1];
    pos+=2;

    return q;
}

DNS_QUESTION dns_question_init(uint16_t qclass, uint16_t qtype) {

    DNS_QUESTION s_question = {0};
    
    s_question.qclass = qclass; // usually 1
    s_question.qtype  = qtype;  // usually 1

    return s_question;
}

int dns_question_serialize(unsigned char *question, unsigned char *domain, DNS_QUESTION s_question) {

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

    question[pos++] = (s_question.qtype >> 8)  & 0b11111111;
    question[pos++] = (s_question.qtype)       & 0b11111111;

    question[pos++] = (s_question.qclass >> 8) & 0b11111111;
    question[pos++] = (s_question.qclass)      & 0b11111111;

    int question_size = pos;
    
    return question_size;
}