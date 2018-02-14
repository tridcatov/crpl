#ifndef DISMESSAGE_H
#define DISMESSAGE_H

#include "messages.h"

class Buffer;

class DisMessage : public Message
{
    friend class MessageReader;
protected:
    virtual Buffer * inscribeMessage(Buffer *) const;
    virtual void readMessage(Buffer *);
public:
    DisMessage();
};

#endif // DISMESSAGE_H
