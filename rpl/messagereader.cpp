#include "messagereader.h"
#include "messages.h"
#include "dismessage.h"
#include "diomessage.h"
#include "buffer.h"

Message * MessageReader::fromBuffer(Buffer * b)
{
    return fromBuffer(b->buf, b->len);
}

Message * MessageReader::fromBuffer(char *buf, int len)
{
    if ( len == 0 )
        return 0;

    int code = buf[0];
    Message * message;
    switch(code) {
    case RplCode::DIS:
        message = new DisMessage();
        break;
    case RplCode::DIO:
        message = new DioMessage();
        break;
    default:
        return 0;
    }
    message->readMessage(buf, len);
    return message;
}

Buffer * MessageReader::toBuffer(Message * msg)
{
    return msg->compileMessage();
}
