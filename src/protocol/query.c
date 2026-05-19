#include "../../include/query.h"

/* Merge Header and Question */
void dns_build_query(unsigned char *query, unsigned char *header, int header_size, unsigned char *question, int question_size) {

    memcpy(query, header, header_size);
    memcpy(query + header_size, question, question_size);
}