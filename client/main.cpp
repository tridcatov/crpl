#include "logging.h"
#include "rpl.h"

#include "messages.h"
#include "dismessage.h"
#include "daomessage.h"
#include "diomessage.h"

#include "address.h"
#include "buffer.h"
#include "rplpad1option.h"
#include "rplpadnoption.h"
#include "rplsolicitedinformationoption.h"
#include "targetoption.h"
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
    instance.dodagid = netconf.getSelfAddress();
    instance.id = 42;
    instance.version = 3;

    Rpl rpl(&io, &netconf, instance, true);

    testDis(io, netconf, instance);
    testDao(io, netconf, instance);
    testDio(io, netconf, instance);

    rpl.print();

    return 0;
}

static void testDis(IOAgent & agent,
                    const NetconfAgent & netconf,
                    const RplInstance & instance) {

    DEBUG("------- Testing DIS solicitation -------");
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

    Buffer buf;
    dis.compileMessage(&buf);
    buf.printHex();

    Message * disDeserialized = MessageReader::fromBuffer(buf);
    if ( disDeserialized->optionNumber() != 4 ) {
        ERR("Deserialization failed");
    } else {
        WARN("Exactly 4 options parsed");
    }

    agent.processInput(addr, buf.buf, buf.len);
    delete disDeserialized;
}

void testDao(IOAgent & io,
             const NetconfAgent & nc,
             const RplInstance & ri)
{
    DEBUG("------- Testing DAO advertisments -------");
    Address addr = nc.getBroadcastAddress();
    addr.u8[15] = 0x03;

    Node node;
    node.address = addr;
    node.instance = ri;
    node.rank = 500;
    node.print();

    NodeList advertisments;
    advertisments.push_back(&node);

    DaoMessage dao(ri, advertisments);
    node.address.u8[15]++;
    TargetOption target1(node);
    dao.addOption(&target1);

    node.address.u8[15]++;
    TargetOption target2(node);
    dao.addOption(&target2);

    node.address.u8[15]++;
    TargetOption target3(node);
    dao.addOption(&target3);

    Buffer buf;
    dao.compileMessage(&buf);
    DEBUG("DAO serialized contents");
    buf.printHex();

    Message * daoDeserialized = MessageReader::fromBuffer(buf);

    io.processInput(addr, buf.buf, buf.len);
}

void testDio(IOAgent & io,
             const NetconfAgent & nc,
             const RplInstance & ri)
{
    DEBUG("------- Testing DIO advertisments -------");

    Address addr = nc.getBroadcastAddress();
    addr.u8[15] = 0x01;

    Node node;
    node.address = addr;
    node.instance = ri;
    node.rank = 200;

    DioMessage dio(node);

    Buffer buf;
    dio.compileMessage(&buf);
    DEBUG("DIO buffer contents:");
    buf.printHex();
    dio.compileMessage(&buf);

    io.processInput(addr, buf.buf, buf.len);
}
