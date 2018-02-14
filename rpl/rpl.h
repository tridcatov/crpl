#ifndef RPL_H
#define RPL_H

class RplInstance;
class IOAgent;
class Node;

#include <list>

class Rpl {
private:
    RplInstance * instance;
    IOAgent * io;
public:
    Rpl(IOAgent * io);
    Node * getMostSutableParent();
    std::list<Node *> getChildren();
    std::list<Node *> getParents();
};

#endif // RPL_H
