#ifndef MESSAGES_H
#define MESSAGES_H

#include "definitions.h"

#include <list>

namespace rpl {

class RplOption;
class Buffer;

using OptionsList = std::list<RplOption *>;

class Message {
private:
  Message() {}
  friend class MessageReader;
public:
  enum Code {
    NONE = 0xff,
    DIS = 0x00,
    DIO = 0x01,
    DAO = 0x02,
    DAO_ACK = 0x03
  };
protected:
  Code code;
  OptionsList options;

  Message(Code code) : code(code) {}

  virtual void inscribeMessage(Buffer *) const = 0;
  virtual void readMessage(const char *, int) = 0;

  void inscribeOptions(Buffer *) const;
public:
  Code getCode() const { return code; }
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

}
#endif // MESSAGES_H
