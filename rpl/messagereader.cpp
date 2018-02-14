#include "messagereader.h"
#include "messages.h"
#include "dismessage.h"
#include "diomessage.h"
#include "buffer.h"

Message * MessageReader::fromBuffer(Buffer * b)
{
    if ( b->len == 0 )
        return 0;

    int code = b->buf[0];
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
    message->readMessage(b);
    return message;
}

Buffer * MessageReader::toBuffer(Message * msg)
{
    return msg->compileMessage();
}
