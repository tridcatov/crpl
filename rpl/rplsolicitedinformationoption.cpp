#include "rplsolicitedinformationoption.h"
#include "rplInstance.h"

RplSolicitedInformationOption::RplSolicitedInformationOption(const RplInstance &inst)
    : RplOption(SOLICITED_INFORMATION)
{
    instanceId = inst.getId();
    versionNumber = inst.getVersion();
    dodagid = inst.getDID();

    matchVersion = true;
    matchInstance = true;
    matchDID = true;
}

static int mvFlag = 1 << 7;
static int miFlag = 1 << 6;
static int mdFlag = 1 << 5;

RplSolicitedInformationOption::RplSolicitedInformationOption(char *buf)
    : RplOption(SOLICITED_INFORMATION)
{
    int flags = buf[3];
    matchVersion = flags & mvFlag;
    matchInstance = flags & miFlag;
    matchDID = flags & mdFlag;

    if ( matchDID )
        for (int i = 0; i < 16; i++)
            dodagid.u8[i] = buf[i + 4];

    instanceId = buf[2];
    versionNumber = buf[20];
}

char * RplSolicitedInformationOption::inscribeInBuffer(char *buf) const
{
    buf[0] = 0x07;
    buf[1] = (char)optLength();
    buf[2] = (char)instanceId;

    int flags = 0;
    if ( matchVersion ) flags |= mvFlag;
    if ( matchInstance ) flags |= miFlag;
    if ( matchDID ) flags |= mdFlag;
    buf[3] = (char)flags;

    for (int i = 0; i < 16; i++)
        buf[i + 4] = matchDID ? dodagid.u8[i] : 0x00;

    buf[20] = (char)versionNumber;
    return buf + length();
}
