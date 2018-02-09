#include "dummyioagent.h"
#include "logging.h"
#include "messages.h"

REGISTER_COMPONENT("DummyIOAgent");

DummyIOAgent::DummyIOAgent() {}

void DummyIOAgent::processInput(const Address &sender, Message *message) {
    DEBUG("Processing input callback");
}

void DummyIOAgent::sendOutput(const Address &receiver, Message *message) {
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
        WARN("Sending raw buffer, not an rpl message");
    }
}
