#include "dummyioagent.h"
#include "logging.h"
#include "messages.h"
#include "messagereader.h"
#include "buffer.h"
#include "rpl.h"

REGISTER_COMPONENT("DummyIOAgent");

using namespace rpl;

DummyIOAgent::DummyIOAgent() {}

static Buffer outputBuffer;

using RplCode = Message::Code;

void DummyIOAgent::sendOutput(const Address &receiver, Message *message) {
  DEBUG("Outgoing message to");
  receiver.print();

  switch (message->getCode()) {
  case RplCode::DAO:
    DEBUG("Sending DAO");
    break;
  case RplCode::DIO:
    DEBUG("Sending DIO");
    break;
  case RplCode::DIS:
    DEBUG("Sending DIS");
    break;
  default:
    ERR("Sending raw buffer, not an rpl message");
  }
  DEBUG("Outgoing message contents:");
  message->compileMessage(&outputBuffer);
  outputBuffer.printHex();
}

void DummyIOAgent::broadcastOutput(Message *) {
  DEBUG("Broadcasting message");
}
