#include "logging.h"

REGISTER_COMPONENT("MAIN");

int main(int argc, char ** argv) {
  DEBUG("debug works");
  WARN("warning works");
  ERR("error works");
  return 0;
}
