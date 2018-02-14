#include "dismessage.h"
#include "buffer.h"
#include "optionreader.h"

#include <stdexcept>

using RE = std::runtime_error;

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


void DisMessage::readMessage(Buffer * b) {
    int length = b->len;
    if ( length <= baseLen )
        throw new RE("Malformed DIS message");

    if ( length == baseLen) return;
    options = OptionReader::readOptions(b->buf + baseLen, length - baseLen);
}
