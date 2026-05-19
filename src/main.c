#include "../include/dns_builder.h"


int main() {

    unsigned char header[512];

    build_dns_header(header);

    return 0;
}