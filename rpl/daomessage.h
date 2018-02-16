#ifndef DAOMESSAGE_H
#define DAOMESSAGE_H

#include "messages.h"
#include "address.h"

class RplInstance;

class DaoMessage : public Message
{
    friend class MessageReader;
private:
    int instanceId;
    bool ackRequired;
    bool dodagAnnouncing;
    Address dodagid;
    int sequence;

    static int generateDaoSequence();
protected:
    virtual void readMessage(char *, int);
    virtual Buffer * inscribeMessage(Buffer *) const;
    virtual bool optionIsAcceptable(RplOption *) const;
public:
    DaoMessage();
    DaoMessage(const RplInstance &);
    virtual ~DaoMessage() {}
};

#endif // DAOMESSAGE_H
