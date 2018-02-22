#ifndef NODE_H
#define NODE_H

#include "address.h"
#include "rplInstance.h"

namespace rpl {

class Node {
public:
  int rank;
  Address address;
  RplInstance instance;

  static inline int infiniteRank() {
    return 1 << 15;
  }

  bool operator==(const Node & o) const {
    return address == o.address;
  }

  void print() const;

  void operator=(const Node & o) {
    rank = o.rank;
    address = o.address;
    instance = o.instance;
  }
};

}
#endif // NODE_H
