#include "rplsolicitedinformationoption.h"
#include "rplInstance.h"

RplSolicitedInformationOption::RplSolicitedInformationOption(RplInstance * inst)
    : RplOption(SOLICITED_INFORMATION)
{
    instanceId = inst->getId();
    versionNumber = inst->getVersion();
    dodagid = inst->getDID();

    matchVersion = true;
    matchInstance = true;
    matchDID = true;
}

char *RplSolicitedInformationOption::inscribeInBuffer(char *buf) const
{
    buf[0] = 0x07;
    buf[1] = (char)optLength();
    buf[2] = (char)instanceId;

    char flags = 0;
    if ( matchVersion ) flags |= (1 << 7);
    if ( matchInstance ) flags |= (1 << 6);
    if ( matchDID ) flags |= (1 << 5);
    buf[3] = (char)flags;

    for (int i = 0; i < 16; i++)
        buf[i + 4] = matchDID ? dodagid.u8[i] : 0x00;

    buf[20] = (char)versionNumber;
    return buf + length();
}
