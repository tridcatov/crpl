#include "ioagent.h"
#include "address.h"
#include "messagereader.h"
#include "diomessage.h"
#include "daomessage.h"
#include "rpl.h"

#include "logging.h"
REGISTER_COMPONENT("IOAgent");

void IOAgent::processInput(const Address &sender, char * buf, int len) {
    try {
        Message * message = MessageReader::fromBuffer(buf, len);
        switch (message->getCode()) {
        case RplCode::DIO:
            rpl->processDio((DioMessage *)message, sender);
            break;
        case RplCode::DAO:
            rpl->processDao((DaoMessage *)message, sender);
            break;
        case RplCode::DIS:
            rpl->processDis((DisMessage *)message, sender);
            break;
        default:
            ERR("RPL message of unsupported type");
        }
    } catch ( ... ) {
        ERR("Invalid message received by daemon");
    }
}
