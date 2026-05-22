#include "../../../include/query.h"

/* Merge Header and Question */
void dns_build_query(unsigned char *buffer, unsigned char *header, int header_size, unsigned char *question, int question_size) {

    memcpy(buffer, header, header_size);
    memcpy(buffer + header_size, question, question_size);
}
