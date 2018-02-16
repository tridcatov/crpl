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

    Node(const Address & addr, int rank = infiniteRank())
        : rank(rank),
          address(addr)
    {

    }

    void setRank(int rank) { this->rank = rank; }

    static inline int infiniteRank() {
        return 1 << 15;
    }

    bool operator==(const Node & o) const {
        return address == o.getAddress();
    }
};


#endif // NODE_H
