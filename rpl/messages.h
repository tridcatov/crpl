#ifndef MESSAGES_H
#define MESSAGES_H

#include "definitions.h"

#define MAX_MESSAGE_LEN 512 * 4
class Message {
    RplCode code;
    char buf[MAX_MESSAGE_LEN];
    int len;
protected:
    Message(RplCode code): code(code), len(0) {}
public:
    static Message * getDIO() {
        return new Message(RplCode::DIO);
    }

    static Message * getDAO() {
        return new Message(RplCode::DAO);
    }

    static Message * getDIS() {
        return new Message(RplCode::DIS);
    }

    void setBuffer(const char * src, int length);
    inline int getLength() const { return len; }
    const char * getBuffer() const { return buf; }
    const char * getCStr();
    inline RplCode getCode() const { return code; }

};

#endif // MESSAGES_H
