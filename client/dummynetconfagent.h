#ifndef DUMMYNETCONFAGENT_H
#define DUMMYNETCONFAGENT_H

#include "netconfagent.h"

class DummyNetconfAgent : public rpl::NetconfAgent
{
private:
  int deviceId;
public:
  DummyNetconfAgent(int deviceId);
  virtual ~DummyNetconfAgent() {}
  virtual const rpl::Address & getBroadcastAddress() const;
  virtual const rpl::Address & getSelfAddress() const;
};

#endif // DUMMYNETCONFAGENT_H
