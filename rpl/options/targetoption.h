#ifndef TARGETOPTION_H
#define TARGETOPTION_H

#include "rploption.h"
#include "address.h"

class Node;

class TargetOption : public RplOption
{
public:
    inline int prefixLength() const {
        return 16;
    }

    inline int optionLength() const {
        return prefixLength() + 2;
    }

    Address addr;

public:
    TargetOption(const Node &);
    TargetOption(const char * buf);

    virtual char *inscribeInBuffer(char * buf) const;

    virtual ~TargetOption() {}

    virtual int length() const {
        return optionLength() + 2;
    }
};

#endif // TARGETOPTION_H
