#ifndef MESSAGES_H
#define MESSAGES_H

#include "definitions.h"

#include <list>

class RplOption;
class Buffer;

class Message {
private:
    Message() {}
    friend class MessageReader;
protected:
    RplCode code;
    std::list<RplOption *> options;

    Message(RplCode code) : code(code) {}

    virtual Buffer * inscribeMessage(Buffer *) const = 0;
    virtual void readMessage(char *, int) = 0;

    Buffer * inscribeOptions(Buffer *) const;
public:
    RplCode getCode() const { return code; }
    virtual ~Message();
    void addOption(RplOption * opt) {
        if ( optionIsAcceptable(opt) )
            options.push_back(opt);
    }
    virtual bool optionIsAcceptable(RplOption *) const = 0;
    Buffer * compileMessage() const;
    inline int optionNumber() const { return options.size(); }
};

#endif // MESSAGES_H
