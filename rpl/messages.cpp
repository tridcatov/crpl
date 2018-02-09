#include "messages.h"

#include "string.h"

void Message::setBuffer(const char *src, int length) {
    memcpy(buf, src, length);
    len = length;
    code = RplCode::NONE;
}

const char * Message::getCStr() {
    buf[len] = '\0';
    return buf;
}
