#include "zlib.h"

#include <stdio.h>
#include <stdint.h>

typedef enum {
	LL_DEBUG = 0,
	LL_INFO,
	LL_WARNING,
	LL_ERROR,
} LogLevel;

void xnu_zlib_inflate(unsigned char *data, uint64_t len) {
#define CHUNK 16384
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char out[CHUNK];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    if (inflateInit2(&strm, 16 + MAX_WBITS) != Z_OK) {
		printf("[-] inflateInit2 failed!\n");
        return ;
    }
	printf("[+] inflateInit2 succeed!\n");

    strm.avail_in = len;
    strm.next_in = data;
    do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        ret = inflate(&strm, Z_NO_FLUSH);
        switch (ret) {
            case Z_NEED_DICT:
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
				printf("[-] inflate failed!\n");
                return ;
        }
        have = CHUNK - strm.avail_out;
    } while (strm.avail_out == 0);

	printf("[+] inflate succeed!\n");
    if (inflateEnd(&strm) != Z_OK) {
		printf("[-] inflateEnd failed!\n");
        return;
    } else {
		printf("[+] inflateEnd succeed!\n");
	}
}

int main(int argc, char **argv) {
    
    unsigned char buffer[2*2014*1024] = { 0 };

	FILE *fp = NULL;
	if (argc == 2) {
		fp = fopen(argv[1], "rb");
		if (fp == NULL) {
			printf("[-] fopen failed, file is %s\n", argv[1]);
			return 0;
		}
		printf("[+] Read from %s\n", argv[1]);
	} else {
		fp = stdin;
		printf("[+] Read from stdin!\n");
	}

	size_t rsize = fread(buffer, 1, sizeof(buffer), fp);
	
	if (rsize <= 0) {
		printf("[-] fread failed!\n");
		return 0;
	}
    xnu_zlib_inflate(buffer, rsize);
    return 0;
}
