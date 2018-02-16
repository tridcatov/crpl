#include "logging.h"
#include "rpl.h"

#include "messages.h"
#include "dismessage.h"
#include "daomessage.h"

#include "address.h"
#include "buffer.h"
#include "rplpad1option.h"
#include "rplpadnoption.h"
#include "rplsolicitedinformationoption.h"
#include "rplInstance.h"
#include "messagereader.h"

#include "dummynetconfagent.h"
#include "dummyioagent.h"


REGISTER_COMPONENT("MAIN");

static void testDio(IOAgent &, const NetconfAgent &, const RplInstance &);
static void testDis(IOAgent &, const NetconfAgent &, const RplInstance &);
static void testDao(IOAgent &, const NetconfAgent &, const RplInstance &);

int main(int argc, char ** argv) {
    DEBUG("debug works");
    WARN("warning works");
    ERR("error works");

    DummyIOAgent io;
    DummyNetconfAgent netconf(2);

    RplInstance instance;
    instance.setDID(netconf.getSelfAddress());
    instance.setId(42);
    instance.setVersion(3);

    Rpl rpl(&io, &netconf, &instance, true);

    testDis(io, netconf, instance);
    testDao(io, netconf, instance);

    return 0;
}

static void testDis(IOAgent & agent,
                    const NetconfAgent & netconf,
                    const RplInstance & instance) {
    Address addr = netconf.getBroadcastAddress();
    addr.u8[15] = 0xfe;

    DisMessage dis;
    agent.sendOutput(addr, &dis);
    agent.broadcastOutput(&dis);

    RplOption * opt = new RplPad1Option();
    dis.addOption(opt);

    opt = new RplPadNOption(4);
    dis.addOption(opt);


    opt = new RplSolicitedInformationOption(instance);
    dis.addOption(opt);

    opt = new RplPadNOption(3);
    dis.addOption(opt);

    Buffer * buf = dis.compileMessage();
    buf->printHex();

    Message * disDeserialized = MessageReader::fromBuffer(buf);
    if ( disDeserialized->optionNumber() != 4 ) {
        ERR("Deserialization failed");
    } else {
        WARN("Exactly 4 options parsed");
    }

    agent.processInput(addr, buf->buf, buf->len);
    delete disDeserialized;
    delete buf;
}

void testDao(IOAgent & io,
             const NetconfAgent & nc,
             const RplInstance & ri)
{
    Address addr = nc.getSelfAddress();
    DaoMessage dao(ri);

    Buffer * buf = dao.compileMessage();
    DEBUG("DAO serialized contents");
    buf->printHex();

    Message * daoDeserialized = MessageReader::fromBuffer(buf);

    io.processInput(addr, buf->buf, buf->len);
    delete buf;
}

