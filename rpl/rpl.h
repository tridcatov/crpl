#ifndef RPL_H
#define RPL_H

#include <list>
#include <map>

#include "node.h"

namespace rpl {

class IOAgent;
class NetconfAgent;

class Message;
class DisMessage;
class DioMessage;
class DaoMessage;

class Address;


using NodeList = std::list<Node *>;
using HopMap = std::map<Address, Address>;
using HopInfo = std::pair<Address, Address>;

class Rpl {
private:
  IOAgent * io;
  NetconfAgent * net;

  NodeList neighbors;
  NodeList children;
  NodeList parents;
  HopMap routables;

  Node node;
  Node m_parent;

  bool root;
private:
  void processDis(DisMessage *, const Address &);
  void processDao(DaoMessage *, const Address &);
  void processDio(DioMessage *, const Address &);

  const Node * getMostSutableParent() const;
public:
  Rpl(IOAgent * io, NetconfAgent * net, const RplInstance & ri, bool isRoot = false);

  const NodeList& getChildren() const { return children; }
  const NodeList& getParents() const { return parents; }
  const NodeList& getNeighbors() const { return neighbors; }
  const HopMap & getRoutingInfo() const { return routables; }

  const Node & self() const { return node; }
  const Node & parent() const { return m_parent; }

  bool hasNeighbor(const Address &) const;

  void processMessage(Message *, const Address &);

  void print() const;
};

}
#endif // RPL_H
