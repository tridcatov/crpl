#ifndef MESSAGEREADER_H
#define MESSAGEREADER_H

namespace rpl {

class Message;
class Buffer;

class MessageReader
{
public:
  static Message * fromBuffer(const Buffer & buf);
  static Message * fromBuffer(const char *buf, int len);
  static Buffer * toBuffer(Message * msg);
};

}

#endif // MESSAGEREADER_H
