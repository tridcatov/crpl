#include "logging.h"
#include "dummyioagent.h"
#include "messages.h"
#include "address.h"

REGISTER_COMPONENT("MAIN");

int main(int argc, char ** argv) {
    DEBUG("debug works");
    WARN("warning works");
    ERR("error works");

    DummyIOAgent * agent = new DummyIOAgent();
    Address addr;
    agent->sendOutput(addr, Message::getDAO());
    agent->sendOutput(addr, Message::getDIO());
    agent->sendOutput(addr, Message::getDIS());
    return 0;
}
