#include "buffer.h"
#include "logging.h"
#include "definitions.h"

REGISTER_COMPONENT("Buffer");

using namespace rpl;

void Buffer::printHex() const {
#if LOGGING_ENABLED == 1
  DEBUG("hex trace");
  printf("\tCode:  %02x", buf[0]);
  for(int i = 0; i < len - 1; i++) {
    if ( i % HEX_BUFFER_OCTETS_IN_LINE == 0 )
      printf("\n\t%04x:", i);
    if ( i % HEX_BUFFER_OCTETS_IN_GROUP == 0 )
      printf("  ");
    printf("%02x ", (unsigned char)buf[i + 1]);
  }
  printf("\n");
#endif // LOGGING_ENABLED
}
