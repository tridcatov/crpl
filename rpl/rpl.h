#ifndef RPL_H
#define RPL_H

class IOAgent;
class NetconfAgent;

class RplInstance;
class Node;

class DisMessage;
class DioMessage;
class DaoMessage;

class Address;

#include <list>

using NodeList = std::list<Node *>;

class Rpl {
private:
    RplInstance * instance;

    IOAgent * io;
    NetconfAgent * net;

    NodeList children;
    NodeList parents;
    Node * thisNode;

    bool root;
public:
    Rpl(IOAgent * io, NetconfAgent * net, bool isRoot = false);

    Node * getMostSutableParent() const;
    const NodeList& getChildren() const { return children; }
    const NodeList& getParents() const { return parents; }

    void processDis(DisMessage *, const Address &);
    void processDao(DaoMessage *, const Address &);
    void processDio(DioMessage *, const Address &);
};

#endif // RPL_H
