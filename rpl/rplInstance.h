#ifndef RPLINSTANCE_H
#define RPLINSTANCE_H

#include "address.h"

namespace rpl {

class RplInstance {
public:
  int id;
  int version;
  Address dodagid;

  void print() const;
  void operator=(const RplInstance & o) {
    id = o.id;
    version = o.version;
    dodagid = o.dodagid;
  }
};

}
#endif // RPLINSTANCE_H

