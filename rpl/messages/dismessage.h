#ifndef DISMESSAGE_H
#define DISMESSAGE_H

#include "messages.h"

namespace rpl {

class Buffer;

class DisMessage : public Message
{
  friend class MessageReader;
protected:
  virtual void inscribeMessage(Buffer *) const;
  virtual void readMessage(const char *, int len);
  virtual bool optionIsAcceptable(RplOption *) const;
public:
  DisMessage();
};

}

#endif // DISMESSAGE_H
