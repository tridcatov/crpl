#ifndef DUMMYIOAGENT_H
#define DUMMYIOAGENT_H

#include "ioagent.h"
namespace rpl {

class DummyIOAgent : public IOAgent
{
public:
  DummyIOAgent();
  virtual void sendOutput(const Address & receiver, Message * message);
  virtual void broadcastOutput(Message * message);
};

}

#endif // DUMMYIOAGENT_H
