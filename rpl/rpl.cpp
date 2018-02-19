#include "rpl.h"
#include "ioagent.h"
#include "netconfagent.h"
#include "logging.h"
#include "address.h"
#include "node.h"
#include "rplInstance.h"

#include "messages.h"
#include "diomessage.h"

#include "util.h"

#include <mutex>

REGISTER_COMPONENT("RPLDaemon");

Rpl::Rpl(IOAgent *io, NetconfAgent *net, const RplInstance &ri, bool isRoot):
    io(io),
    net(net),
    root(isRoot)
{
    node.address = net->getSelfAddress();
    io->setRplDaemon(this);
    if ( isRoot ) {
        node.rank = 0;
        node.instance.dodagid = net->getSelfAddress();
        node.instance.version = 0;
        node.instance.id = Util::shortIntFromBuffer((const char *)node.instance.dodagid.u8 + 14);
    }
}

static bool hasNode(const Address & address, const NodeList & nl) {
    for(NodeList::const_iterator i = nl.begin(); i != nl.end(); i++) {
        const Node & n = **i;
        if ( n.address == address )
            return true;
    }

    return false;
}

bool Rpl::hasNeighbor(const Address &address) const
{
    return hasNode(address, neighbors);
}

void Rpl::processMessage(Message * message, const Address & sender)
{
    if ( sender == net->getSelfAddress() ) {
        WARN("Received message from current node, possible loop storm");
        return;
    }

    DEBUG("Received RPL message from:");
    sender.print();

    switch (message->getCode()) {
    case RplCode::DIO:
        processDio((DioMessage *)message, sender);
        break;
    case RplCode::DAO:
        processDao((DaoMessage *)message, sender);
        break;
    case RplCode::DIS:
        processDis((DisMessage *)message, sender);
        break;
    default:
        ERR("RPL message of unsupported type");
    }
}

static std::mutex processingMutex;
using Lock = std::lock_guard<std::mutex>;
#define LOCK Lock lock(processingMutex)

void Rpl::processDis(DisMessage * msg, const Address & sender) {
    LOCK;
    DEBUG("Processing DIS RPL message...");
    Node neighbor;
    neighbor.address = sender;

    if ( hasNeighbor(sender) )
        WARN("Neighbor is already in cache, possible resolicit");
    else {
        DEBUG("Adding neighbor to cache with address:");
        sender.print();
        neighbors.push_back(new Node(neighbor));
    }

    DEBUG("Unicast reply to sender");

    DioMessage dio(node);
    io->sendOutput(sender, &dio);
}

void Rpl::processDao(DaoMessage *, const Address &) {
    LOCK;
    DEBUG("Processing incoming RPL DAO message");
}

void Rpl::processDio(DioMessage * m, const Address & sender) {
    LOCK;
    DEBUG("Processing incoming RPL DIO message");

    Node * n = new Node();
    n->address = sender;
    n->instance.dodagid = m->dodagid;
    n->rank = m->rank;

    if ( !hasNeighbor(sender) ) {
        DEBUG("Discovered neighbor via DIO");
        sender.print();
        neighbors.push_back(n);
    }

    if ( parents.empty() ) {
        DEBUG("No parents present, adding parent and updating instance");
        parents.push_back(n);
        node.instance = n->instance;
        node.rank = n->rank + 1;
    }
}
