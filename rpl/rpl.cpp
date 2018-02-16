#include "rpl.h"
#include "ioagent.h"
#include "netconfagent.h"
#include "logging.h"
#include "address.h"

#include <mutex>

REGISTER_COMPONENT("RPLDaemon");

Rpl::Rpl(IOAgent *io, NetconfAgent *net, bool isRoot):
    io(io),
    net(net),
    root(isRoot)
{
    io->setRplDaemon(this);
}

static std::mutex processingMutex;
using Lock = std::lock_guard<std::mutex>;
#define LOCK Lock lock(processingMutex)

void Rpl::processDis(DisMessage * msg, const Address & sender)
{
    LOCK;
    DEBUG("Processing incoming RPL DIS message from:");
    sender.print();
}

void Rpl::processDao(DaoMessage *, const Address &)
{
    LOCK;
    DEBUG("Processing incoming RPL DAO message");
}

void Rpl::processDio(DioMessage *, const Address &)
{
    LOCK;
    DEBUG("Processing incoming RPL DIO message");
}
