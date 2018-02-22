#include "rplpadnoption.h"

#include <stdexcept>

using RE = std::runtime_error;
using namespace rpl;

static inline void assertPadding(int padding) {
  if ( padding < 2 || padding > 7 )
    throw new RE("Not allowed padding out of constraints [2, 7]");
}

RplPadNOption::RplPadNOption(int padding)
  : RplOption(RplOption::PADN)
{
  assertPadding(padding);
  this->padding = padding;
}

RplPadNOption::RplPadNOption(const char *buf)
  : RplOption(RplOption::PADN)
{
  int l = buf[1] + 2;
  assertPadding(l);

  padding = l;
}

char * RplPadNOption::inscribeInBuffer(char *buf) const
{
  buf[0] = 0x01;
  buf[1] = (char)padding - 2;
  for( int i = 2; i < padding; i++) {
    buf[i] = 0x00;
  }
  return buf + padding;
}
