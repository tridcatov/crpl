#ifndef RPLOPTION_H
#define RPLOPTION_H

namespace rpl {

class RplOption
{
  friend class OptionReader;
public:
  enum Type {
    PAD1 = 0,
    PADN = 1,
    DAG_METRIC_CONTAINER = 2,
    ROUTING_INFORMATION = 3,
    DODAG_CONFIGURATION = 4,
    RPL_TARGET = 5,
    TRANSIT_INFORMATION = 6,
    SOLICITED_INFORMATION = 7,
    PREFIX_INFORMATION = 8,
    TARGET_DESCRIPTOR = 9
  };
private:
  RplOption() {}
protected:
  Type type;
  RplOption(Type type) : type(type) {}
public:
  virtual char * inscribeInBuffer(char * buf) const = 0;
  virtual ~RplOption() {}
  // virtual char * readOption(char * buf) = 0;
  virtual int length() const = 0;
  inline Type getType() const { return type; }

};

}

#endif // RPLOPTION_H
