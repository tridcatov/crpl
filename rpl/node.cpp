#include "node.h"
#include "logging.h"

REGISTER_COMPONENT("Node");

void Node::print() const {
#if LOGGING_ENABLED == 1
    DEBUG("Node stats:");
    address.print();
    printf("\tRank: %d\n", rank);
    instance.print();
#endif
}
