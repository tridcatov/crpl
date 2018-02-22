#include "rplInstance.h"
#include "logging.h"

using namespace rpl;

void RplInstance::print() const {
#if LOGGING_ENABLED == 1
  printf("\tinstance: %d, version: %d\n", id, version);
  printf("\tdodagid:\n");
  dodagid.print();
#endif
}
