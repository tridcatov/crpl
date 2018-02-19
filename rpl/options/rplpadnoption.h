#ifndef RPLPADNOPTION_H
#define RPLPADNOPTION_H

#include "rploption.h"

class RplPadNOption : public RplOption
{
private:
    int padding;
public:
    RplPadNOption(int padding);
    RplPadNOption(const char * buf);
    virtual char * inscribeInBuffer(char *buf) const;
    virtual int length() const { return padding; }
};

#endif // RPLPADNOPTION_H
