#ifndef DAOMESSAGE_H
#define DAOMESSAGE_H

#include "messages.h"
#include "address.h"

#include <list>

class Node;
using NodeList = std::list<Node *>;

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
    virtual void readMessage(const char *, int);
    virtual void inscribeMessage(Buffer *) const;
    virtual bool optionIsAcceptable(RplOption *) const;
public:
    DaoMessage();
    DaoMessage(const RplInstance &, const NodeList & nodes);
    virtual ~DaoMessage() {}
};

#endif // DAOMESSAGE_H
