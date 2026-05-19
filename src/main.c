#include "../include/dns_builder.h"


int main() {

    //testando apenas

    unsigned char header[12];

    DNS_HEADER s_header = dns_header_init(123, 1, 1);

    dns_header_serialize(header, s_header);

    for (int i = 0; i < 12; i++) {
        printf("header[%d] = 0b%08b\n", i, header[i]);
    }
    return 0;
}