#include "messages.h"
#include "buffer.h"
#include "rploption.h"

using namespace rpl;

using It = std::list<RplOption *>::const_iterator;

void Message::inscribeOptions(Buffer * buffer) const {
  char * b = buffer->buf + buffer->len;
  int optLen = 0;
  for (It o = options.begin(); o != options.end(); o++) {
    RplOption * opt = *o;
    b = opt->inscribeInBuffer(b);
    optLen += opt->length();
  }

  buffer->len += optLen;
}

void Message::compileMessage(Buffer * b) const {
  inscribeMessage(b);
  inscribeOptions(b);
}

Message::~Message()
{
  for(RplOption * opt : options )
    delete opt;
}


