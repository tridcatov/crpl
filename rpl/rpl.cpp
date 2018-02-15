#include "rpl.h"
#include "ioagent.h"
#include "logging.h"

#include <mutex>

REGISTER_COMPONENT("RPLDaemon");

Rpl::Rpl(IOAgent *io, bool isRoot):
    io(io),
    root(isRoot)
{
    io->setRplDaemon(this);
}

static std::mutex processingMutex;
using Lock = std::lock_guard<std::mutex>;
#define LOCK Lock lock(processingMutex)

void Rpl::processDis(DisMessage *, const Address &)
{
    LOCK;
    DEBUG("Processing incoming RPL DIS message");
}

void Rpl::processDao(DaoMessage *, const Address &)
{
    LOCK;
    DEBUG("Processing incoming RPL DIS message");
}

void Rpl::processDio(DioMessage *, const Address &)
{
    LOCK;
    DEBUG("Processing incoming RPL DIS message");
}
