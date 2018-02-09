#include "rpl.h"
#include "ioagent.h"

Rpl::Rpl(IOAgent *io):
    io(io)
{
    io->setRplDaemon(this);
}
