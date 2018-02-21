#ifndef MESSAGES_H
#define MESSAGES_H

#include "definitions.h"

#include <list>

class RplOption;
class Buffer;

using OptionsList = std::list<RplOption *>;

class Message {
private:
    Message() {}
    friend class MessageReader;
protected:
    RplCode code;
    OptionsList options;

    Message(RplCode code) : code(code) {}

    virtual void inscribeMessage(Buffer *) const = 0;
    virtual void readMessage(const char *, int) = 0;

    void inscribeOptions(Buffer *) const;
public:
    RplCode getCode() const { return code; }
    virtual ~Message();
    void addOption(RplOption * opt) {
        if ( optionIsAcceptable(opt) )
            options.push_back(opt);
    }
    virtual bool optionIsAcceptable(RplOption *) const = 0;
    void compileMessage(Buffer * b) const;
    inline int optionNumber() const { return options.size(); }
    inline const OptionsList & getOptions() const { return options; }
};

#endif // MESSAGES_H
