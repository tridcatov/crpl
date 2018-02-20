#include "rpl.h"
#include "ioagent.h"
#include "netconfagent.h"
#include "logging.h"
#include "address.h"
#include "node.h"
#include "rplInstance.h"

#include "rploption.h"
#include "targetoption.h"

#include "messages.h"
#include "diomessage.h"
#include "daomessage.h"

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

using OptionsList = std::list<RplOption *>;
using TargetList = std::list<TargetOption *>;

static TargetList getTargets(const OptionsList & opts) {
    TargetList result;
    for(RplOption * opt : opts) {
        if ( opt->getType() == RplOption::RPL_TARGET )
            result.push_back((TargetOption *) opt);
    }

    return result;
}

void Rpl::processDao(DaoMessage * m, const Address & addr) {
    LOCK;
    DEBUG("Processing incoming RPL DAO message");

    TargetList targets = getTargets(m->getOptions());
    if ( targets.empty() ) {
        WARN("DAO message arrived with no targets to advertise");
        return;
    }

    DEBUG("Adding route entries with nexthop:");
    addr.print();

    for (TargetOption * opt : targets) {
        const Address & target = opt->addr;
        DEBUG("Route target:");
        target.print();
        routables[target] = addr;
    }
}

void Rpl::processDio(DioMessage * m, const Address & sender) {
    LOCK;
    DEBUG("Processing incoming RPL DIO message");

    Node * n = new Node();
    n->address = sender;
    n->rank = m->rank;

    RplInstance & i = n->instance;
    i.dodagid = m->dodagid;
    i.id = m->instanceId;
    i.version = m->versionNumber;

    DEBUG("Parsed following node information from DIO:");
    n->print();


    if ( !hasNeighbor(sender) ) {
        DEBUG("Discovered neighbor via DIO");
        sender.print();
        neighbors.push_back(n);
    }

    if ( !hasNode(sender, parents) ) {
        DEBUG("Adding as parent");
        parents.push_back(n);
    }

    if ( !parents.empty() ) {
        const Node * selectedParent = getMostSutableParent();
        DEBUG("Selected following address as parent:");
        selectedParent->address.print();
        m_parent = *selectedParent;

        DEBUG("Updating ranks");

        node.instance = selectedParent->instance;
        node.rank = selectedParent->rank + 1;
    }
}

const Node * Rpl::getMostSutableParent() const
{
    if ( parents.empty() )
        return 0;

    const Node * result = *parents.begin();
    for ( NodeList::const_iterator i = parents.begin(); i != parents.end(); i++) {
        const Node * candidate = *i;
        if ( candidate->rank < result->rank )
            result = candidate;
    }

    return result;
}

void Rpl::print() const
{
#if LOGGING_ENABLED == 1
    DEBUG("Status information");
    DEBUG("Current node status:");
    node.print();

    DEBUG("Current parent status:");
    m_parent.print();

    printf("\tRoutable entries number: %d\n", routables.size());
    for(const HopInfo & hop : routables ) {
        hop.first.print();
        DEBUG("VIA");
        hop.second.print();
    }
#endif
}
