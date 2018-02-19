#ifndef NODE_H
#define NODE_H

#include "address.h"
#include "rplInstance.h"

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
};


#endif // NODE_H
