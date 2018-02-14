#include "dismessage.h"
#include "buffer.h"

#include <stdexcept>

using RE = std::runtime_error;

DisMessage::DisMessage()
    : Message(RplCode::DIS)
{
}

Buffer * DisMessage::inscribeMessage(Buffer * b) const {
    char * buf = b->buf;

    buf[0] = (char)RplCode::DIS;
    buf[1] = buf[2] = 0;

    b->len = 3;
    return b;
}

void DisMessage::readMessage(Buffer * b) {
    if ( b->len <= 3 )
        throw new RE("Malformed DIS message");
}
