#include "dismessage.h"
#include "buffer.h"
#include "optionreader.h"
#include "rploption.h"

#include <stdexcept>
#include <set>

using RE = std::runtime_error;
using OptionsSet = std::set<RplOption::Type>;

DisMessage::DisMessage()
    : Message(RplCode::DIS)
{
}

static int baseLen = 3;

Buffer * DisMessage::inscribeMessage(Buffer * b) const {
    char * buf = b->buf;

    buf[0] = (char)RplCode::DIS;
    buf[1] = buf[2] = 0;

    b->len = baseLen;
    return b;
}


void DisMessage::readMessage(char * b, int len) {
    if ( len <= baseLen )
        throw new RE("Malformed DIS message");

    if ( len == baseLen) return;
    options = OptionReader::readOptions(b + baseLen, len - baseLen);
}

bool DisMessage::optionIsAcceptable(RplOption * opt) const
{
    static OptionsSet acceptable = {
        RplOption::PAD1,
        RplOption::PADN,
        RplOption::SOLICITED_INFORMATION
    };
    return acceptable.find(opt->getType()) != acceptable.end();
}
