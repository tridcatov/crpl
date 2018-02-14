#include "logging.h"
#include "dummyioagent.h"
#include "messages.h"
#include "dismessage.h"
#include "address.h"
#include "buffer.h"
#include "rplpad1option.h"
#include "rplpadnoption.h"
#include "rplsolicitedinformationoption.h"
#include "rplInstance.h"

REGISTER_COMPONENT("MAIN");

int main(int argc, char ** argv) {
    DEBUG("debug works");
    WARN("warning works");
    ERR("error works");

    DummyIOAgent * agent = new DummyIOAgent();
    Address addr;
    DisMessage dis;
    agent->sendOutput(addr, &dis);
    agent->broadcastOutput(&dis);

    RplOption * opt = new RplPad1Option();
    dis.addOption(opt);

    opt = new RplPadNOption(4);
    dis.addOption(opt);

    addr.u8[0] = 0xfe;
    addr.u8[1] = 0x2e;
    addr.u8[15] = 0x1a;

    RplInstance instance;
    instance.setDID(addr);
    instance.setId(42);
    instance.setVersion(3);

    opt = new RplSolicitedInformationOption(&instance);
    dis.addOption(opt);

    opt = new RplPadNOption(3);
    dis.addOption(opt);

    Buffer * buf = dis.compileMessage();
    buf->printHex();
    delete buf;

    return 0;
}
