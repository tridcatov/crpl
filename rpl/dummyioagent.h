#ifndef DUMMYIOAGENT_H
#define DUMMYIOAGENT_H

#include "ioagent.h"

class DummyIOAgent : public IOAgent
{
public:
    DummyIOAgent();
    virtual void processInput(const Address & sender, Message * message);
    virtual void sendOutput(const Address & receiver, Message * message);
};

#endif // DUMMYIOAGENT_H
