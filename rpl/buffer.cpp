#include "buffer.h"
#include "logging.h"

REGISTER_COMPONENT("Buffer");

void Buffer::printHex() const {
#if LOGGING_ENABLED == 1
    DEBUG("hex trace");
    for(int i = 0; i < len; i++) {
        if ( i % 8 == 0 )
            printf("\n\t%04x:", i);
        if ( i % 4 == 0 )
            printf("  ");
        printf("%02x ", (unsigned char)buf[i]);
    }
    printf("\n");
#endif // LOGGING_ENABLED
}
