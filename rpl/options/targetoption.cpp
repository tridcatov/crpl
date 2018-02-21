#include "targetoption.h"

#include "node.h"

TargetOption::TargetOption(const Address &addr)
    : RplOption(RPL_TARGET),
      addr(addr)
{

}

TargetOption::TargetOption(const char *buf)
    : RplOption(RPL_TARGET)
{
    addr.readFromBuffer(buf + 4);
}

char * TargetOption::inscribeInBuffer(char *b) const
{
    b[0] = (char) getType();
    b[1] = (char) optionLength();
    b[2] = 0;
    b[3] = (char) prefixLength();

    addr.insribeInBuffer(b + 4);
    return b + length();
}
