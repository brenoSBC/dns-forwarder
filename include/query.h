#ifndef QUERY_H
#define QUERY_H

#include <string.h>

void dns_build_query(unsigned char *query, unsigned char *header, int header_size, unsigned char *question, int question_size);

#endif