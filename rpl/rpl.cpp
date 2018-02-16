#include "rpl.h"
#include "ioagent.h"
#include "netconfagent.h"
#include "logging.h"
#include "address.h"
#include "node.h"

#include "messages.h"
#include "diomessage.h"

#include <mutex>

REGISTER_COMPONENT("RPLDaemon");

Rpl::Rpl(IOAgent *io, NetconfAgent *net, RplInstance *ri, bool isRoot):
    io(io),
    net(net),
    instance(ri),
    thisNode(net->getSelfAddress()),
    root(isRoot)
{
    io->setRplDaemon(this);
    if ( isRoot )
        thisNode.setRank(0);
}

bool Rpl::hasNeighbor(const Node & node) const
{
    for(NodeList::const_iterator i = neighbors.begin(); i != neighbors.end(); i++) {
        const Node & neighbor = **i;
        if ( node == neighbor )
            return true;
    }

    return false;
}

void Rpl::processMessage(Message * message, const Address & sender)
{
    if ( sender == net->getSelfAddress() ) {
        WARN("Received message from current node, possible loop storm");
        return;
    }
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
    DEBUG("Processing incoming RPL DIS message from:");
    Node neighbor(sender);

    if ( hasNeighbor(neighbor) )
        WARN("Neighbor is already in cache, possible resolicit");
    else {
        DEBUG("Adding neighbor to cache with address:");
        sender.print();
        neighbors.push_back(new Node(neighbor));
    }

    DEBUG("Unicast reply to sender");
    outputDio(sender);
}

void Rpl::processDao(DaoMessage *, const Address &) {
    LOCK;
    DEBUG("Processing incoming RPL DAO message");
}

void Rpl::processDio(DioMessage *, const Address &) {
    LOCK;
    DEBUG("Processing incoming RPL DIO message");
}

void Rpl::outputDio(const Address & receiver) {
    DioMessage dio(*instance, thisNode);
    DEBUG("Formed raw dio message to announce current instance");
    io->sendOutput(receiver, &dio);
}
