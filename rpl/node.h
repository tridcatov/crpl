#ifndef NODE_H
#define NODE_H

#include "address.h"

class Node {
private:
    int rank;
    Address address;
public:
    int getRank() const { return rank; }
    const Address & getAddress() const {
        return address;
    }
};

#endif // NODE_H
