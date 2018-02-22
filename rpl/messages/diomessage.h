#ifndef DIOMESSAGE_H
#define DIOMESSAGE_H

#include "messages.h"
#include "address.h"

namespace rpl {
class RplInstance;
class Node;

class DioMessage : public Message
{
  friend class MessageReader;
public:
  enum MOP {
    NO_DOWNWARD_ROUTES = 0,
    NON_STORING = 1,
    STORING_NO_MCAST = 2,
    STORING_MCAST = 3
  };
public:
  int instanceId;
  int versionNumber;
  int rank;
  Address dodagid;
  MOP mop;
protected:
  virtual void readMessage(const char *, int);
  virtual void inscribeMessage(Buffer *) const;
  virtual bool optionIsAcceptable(RplOption *) const;

public:
  DioMessage();
  DioMessage(const Node &);
  virtual ~DioMessage() {}
};

}
#endif // DIOMESSAGE_H
