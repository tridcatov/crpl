#ifndef DUMMYNETCONFAGENT_H
#define DUMMYNETCONFAGENT_H

#include "netconfagent.h"

class DummyNetconfAgent : public NetconfAgent
{
private:
    int deviceId;
public:
    DummyNetconfAgent(int deviceId);
    virtual ~DummyNetconfAgent() {}
    virtual const Address & getBroadcastAddress() const;
    virtual const Address & getSelfAddress() const;
};

#endif // DUMMYNETCONFAGENT_H
