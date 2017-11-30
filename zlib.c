#include "zlib.h"

#include <stdio.h>
#include <stdint.h>

void xnu_zlib(uint8_t *data, uint64_t size) {
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = 0;


}

int main() {
    
    char buffer[2*2014*1024] = { 0 };
    size_t rsize = fread(buffer, 1, sizeof(buffer), stdin);
    if (rsize <= 0) {
        return 0;
    }
    xnu_zlib(buffer, rsize);
    return 0;
}
