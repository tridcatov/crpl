#ifndef DIOMESSAGE_H
#define DIOMESSAGE_H

#include "messages.h"
#include "address.h"

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
private:
    int instanceId;
    int versionNumber;
    int rank;
    Address dodagid;
    MOP mop;
protected:
    virtual void readMessage(char *, int);
    virtual Buffer * inscribeMessage(Buffer *) const;
    virtual bool optionIsAcceptable(RplOption *) const;

public:
    DioMessage();
    DioMessage(const RplInstance &, const Node &);
    virtual ~DioMessage() {}

    inline int getInstanceId() const { return instanceId; }
    inline int getVersionNumber() const { return versionNumber; }
    inline int getRank() const { return rank; }
    inline const Address & getDID() const { return dodagid; }
    inline MOP getMop() const { return mop; }
};

#endif // DIOMESSAGE_H
