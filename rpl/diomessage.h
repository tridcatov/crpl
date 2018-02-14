#ifndef DIOMESSAGE_H
#define DIOMESSAGE_H

#include "messages.h"

class DioMessage : public Message
{
    friend class MessageReader;
protected:
    virtual void readMessage(Buffer *);
    virtual Buffer * inscribeMessage(Buffer *) const;
public:
    DioMessage();
};

#endif // DIOMESSAGE_H
