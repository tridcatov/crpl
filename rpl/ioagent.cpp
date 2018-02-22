#include "ioagent.h"
#include "address.h"
#include "messagereader.h"
#include "diomessage.h"
#include "daomessage.h"
#include "rpl.h"

#include "logging.h"
REGISTER_COMPONENT("IOAgent");

using namespace rpl;

void IOAgent::processInput(const Address &sender, char * buf, int len) {
  try {
    Message * message = MessageReader::fromBuffer(buf, len);
    rpl->processMessage(message, sender);
  } catch ( ... ) {
    ERR("Invalid message received by daemon");
  }
}
