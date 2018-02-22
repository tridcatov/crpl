#ifndef IOAGENT_H
#define IOAGENT_H

#include "definitions.h"

namespace rpl {

class Address;
class Message;
class Rpl;

class IOAgent {
protected:
  Rpl * rpl;
public:
  void processInput(const Address & sender, char * buf, int len);
  virtual void sendOutput(const Address & receiver, Message * message) = 0;
  virtual void broadcastOutput(Message * message) = 0;
  void setRplDaemon(Rpl * rpl) { this->rpl = rpl; }
};

}

#endif // IOAGENT
