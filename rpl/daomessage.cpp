#include "daomessage.h"
#include "rplInstance.h"
#include "buffer.h"
#include "rploption.h"
#include "optionreader.h"

#include <set>
#include <stdexcept>

using RE = std::runtime_error;

DaoMessage::DaoMessage()
    : Message(DAO)
{

}

DaoMessage::DaoMessage(const RplInstance &i)
    : Message(DAO)
{
    instanceId = i.getId();
    ackRequired = false;
    dodagAnnouncing = true;
    dodagid = i.getDID();
    sequence = generateDaoSequence();
}


int DaoMessage::generateDaoSequence()
{
    static int sequence = 0;
    return ++sequence;
}

static int baseLenNoAnnounce = 1 + 4;
static int ackRequiredFlag = (1 << 7);
static int didAnnouncedFlag = (1 << 6);

void DaoMessage::inscribeMessage(Buffer * buf) const
{
    char * b = buf->buf;
    b[0] = (char) getCode();
    b[1] = (char) instanceId;

    int flags = 0;
    if ( ackRequired ) flags |= ackRequiredFlag;
    if ( dodagAnnouncing ) flags |= didAnnouncedFlag;
    b[2] = (char) flags;

    b[3] = 0;
    b[4] = (char) sequence;

    int length = baseLenNoAnnounce;
    if ( dodagAnnouncing ) {
        dodagid.insribeInBuffer(b + 5);
        length += sizeof(dodagid);
    }

    buf->len = length;
}

void DaoMessage::readMessage(const char *b, int len)
{
    if ( len < baseLenNoAnnounce )
        throw RE("Malformed DAO message: too short");

    instanceId = b[1];
    ackRequired = b[2] & ackRequiredFlag;
    dodagAnnouncing = b[2] & didAnnouncedFlag;
    sequence = b[4];

    if ( dodagAnnouncing && len < baseLenNoAnnounce + sizeof(Address))
        throw RE("Malformed DAO message: too short");

    if ( dodagAnnouncing )
        dodagid.readFromBuffer(b + 5);

    int skip = baseLenNoAnnounce + ( dodagAnnouncing
            ? sizeof(dodagid)
            : 0 );
    if ( skip == len ) return;
    options = OptionReader::readOptions(b + skip, len - skip);
}

bool DaoMessage::optionIsAcceptable(RplOption * opt) const
{
    static std::set<RplOption::Type> acc = {
        RplOption::PAD1,
        RplOption::PADN,
        RplOption::RPL_TARGET,
        RplOption::TRANSIT_INFORMATION,
        RplOption::TARGET_DESCRIPTOR
    };
    return acc.find(opt->getType()) != acc.end();
}
