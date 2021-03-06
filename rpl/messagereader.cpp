#include "messagereader.h"
#include "messages.h"
#include "dismessage.h"
#include "diomessage.h"
#include "daomessage.h"
#include "buffer.h"

using namespace rpl;

Message * MessageReader::fromBuffer(const Buffer &b)
{
  return fromBuffer(b.buf, b.len);
}

using RplCode = Message::Code;

Message * MessageReader::fromBuffer(const char *buf, int len)
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
  case RplCode::DAO:
    message = new DaoMessage();
    break;
  default:
    return 0;
  }
  message->readMessage(buf, len);
  return message;
}

Buffer * MessageReader::toBuffer(Message * msg)
{
  Buffer * result = new Buffer();
  msg->compileMessage(result);
  return result;
}
