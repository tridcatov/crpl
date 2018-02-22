#ifndef NETCONFAGENT_H
#define NETCONFAGENT_H

#include "address.h"

namespace rpl {

class NetconfAgent {
public:
  virtual const Address & getSelfAddress() const = 0;
  virtual const Address & getBroadcastAddress() const = 0;
  NetconfAgent() {}
};

}
#endif // NETCONFAGENT_H
