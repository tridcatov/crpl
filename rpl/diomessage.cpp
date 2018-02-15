#include "diomessage.h"
#include "rploption.h"
#include "rplInstance.h"
#include "node.h"
#include "buffer.h"
#include "optionreader.h"

#include <set>
#include <stdexcept>

using RE = std::runtime_error;


DioMessage::DioMessage()
    : Message(RplCode::DIO)
{

}

DioMessage::DioMessage(const RplInstance & i, const Node & n)
    : Message(RplCode::DIO)
{
    instanceId = i.getId();
    versionNumber = i.getVersion();
    dodagid = i.getDID();
    mop = STORING_MCAST;
    rank = n.getRank();
}

static int baseLen = 1 + 4 + 4 + sizeof(Address);

void DioMessage::readMessage(char * b, int len)
{
    if ( len < baseLen )
        throw RE("Insufficient DIO message length");

    instanceId = b[1];
    versionNumber = b[2];
    rank = ( b[3] << 8 ) | b[4];
    int mopflags = ( b[5] >> 3 ) & 7;
    switch (mopflags) {

    case NON_STORING:
        mop = NON_STORING;
        break;
    case STORING_NO_MCAST:
        mop = STORING_NO_MCAST;
        break;
    case STORING_MCAST:
        mop = STORING_MCAST;
        break;
    case NO_DOWNWARD_ROUTES:
    default:
        mop = NO_DOWNWARD_ROUTES;
    }

    for(int i = 0; i < 16; i++) {
        dodagid.u8[i] = b[9 + i];
    }

    if ( len == baseLen ) return;
    options = OptionReader::readOptions(b + baseLen, len - baseLen);
}

Buffer *DioMessage::inscribeMessage(Buffer * buf) const
{
    char * b = buf->buf;

    b[0] = (char) getCode();
    b[1] = (char) instanceId;
    b[2] = (char) versionNumber;

    b[3] = (char) rank >> 8;
    b[4] = (char) rank & 0xff;

    char mode = (1 << 7) | (mop << 3);
    b[5] = mode;
    b[6] = b[7] = b[8] = 0;

    for(int i = 0; i < 16; i++) {
        b[9 + i] = dodagid.u8[i];
    }

    buf->len = baseLen;
    return buf;
}

bool DioMessage::optionIsAcceptable(RplOption * opt) const
{
    static std::set<RplOption::Type> acc = {
        RplOption::PAD1,
        RplOption::PADN,
        RplOption::DAG_METRIC_CONTAINER,
        RplOption::ROUTING_INFORMATION,
        RplOption::DODAG_CONFIGURATION,
        RplOption::PREFIX_INFORMATION
    };
    return acc.find(opt->getType()) != acc.end();
}

