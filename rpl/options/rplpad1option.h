#ifndef RPLPAD1OPTION_H
#define RPLPAD1OPTION_H

#include "rploption.h"

class RplPad1Option : public RplOption
{
public:
    RplPad1Option();
    RplPad1Option(const char *) : RplOption(PAD1) {}
    virtual ~RplPad1Option() {}
    virtual char * inscribeInBuffer(char *buf) const;
    virtual int length() const { return 1; }
};

#endif // RPLPAD1OPTION_H
