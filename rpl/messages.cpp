#include "messages.h"
#include "buffer.h"
#include "rploption.h"

using It = std::list<RplOption *>::const_iterator;

Buffer * Message::inscribeOptions(Buffer * buffer) const {
    char * b = buffer->buf + buffer->len;
    int optLen = 0;
    for (It o = options.begin(); o != options.end(); o++) {
        RplOption * opt = *o;
        b = opt->inscribeInBuffer(b);
        optLen += opt->length();
    }

    buffer->len += optLen;
    return buffer;
}

Buffer * Message::compileMessage() const {
    Buffer * result = new Buffer();
    result = inscribeMessage(result);
    return inscribeOptions(result);
}

Message::~Message() {
    for(It o = options.begin(); o != options.end(); o++)
        delete *o;
}
