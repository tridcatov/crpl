#ifndef MESSAGEREADER_H
#define MESSAGEREADER_H

class Message;
class Buffer;

class MessageReader
{
public:
    static Message * fromBuffer(Buffer * buf);
    static Buffer * toBuffer(Message * msg);
};

#endif // MESSAGEREADER_H
