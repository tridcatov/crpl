#ifndef RPLSOLICITEDINFORMATIONOPTION_H
#define RPLSOLICITEDINFORMATIONOPTION_H

#include "rploption.h"
#include "address.h"

class RplInstance;

class RplSolicitedInformationOption : public RplOption
{
private:
    inline int optLength() const { return 19; }
    int instanceId;
    int versionNumber;
    Address dodagid;
    bool matchVersion;
    bool matchInstance;
    bool matchDID;
public:
    RplSolicitedInformationOption(const RplInstance &);
    RplSolicitedInformationOption(const char * buf);
    virtual int length() const { return optLength() + 2; }
    virtual char * inscribeInBuffer(char *buf) const;

    inline bool shouldMatchVersion() const { return matchVersion; }
    inline bool shouldMatchInstance() const { return matchInstance; }
    inline bool shouldMatchDID() const { return matchDID; }
};

#endif // RPLSOLICITEDINFORMATIONOPTION_H
