#include "dummynetconfagent.h"

using rpl::Address;

DummyNetconfAgent::DummyNetconfAgent(int deviceId)
  : NetconfAgent(),
    deviceId(deviceId)
{

}

static const Address & broadcastAddress() {
  static Address ba = Address::getPrivateBroadcastAddress();
  return ba;
}

const Address & DummyNetconfAgent::getBroadcastAddress() const
{
  return broadcastAddress();
}

const Address & DummyNetconfAgent::getSelfAddress() const
{
  static Address addr = broadcastAddress();
  addr.u8[15] = deviceId & 0xff;
  if ( deviceId > 0xff )
    addr.u8[14] = ( deviceId >> 8 ) & 0xff;

  return addr;
}
