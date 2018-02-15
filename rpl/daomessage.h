#ifndef DAOMESSAGE_H
#define DAOMESSAGE_H

#include "messages.h"

class DaoMessage : public Message
{
    friend class MessageReader;
protected:
    virtual void readMessage(char *, int) {}
    virtual Buffer * inscribeMessage(Buffer *) const { return 0; }
public:
    DaoMessage();
    virtual ~DaoMessage() {}
};

#endif // DAOMESSAGE_H
