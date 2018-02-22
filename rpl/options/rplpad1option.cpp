#include "rplpad1option.h"

using namespace rpl;

RplPad1Option::RplPad1Option()
  : RplOption(RplOption::PAD1)
{

}

char * RplPad1Option::inscribeInBuffer(char *buf) const
{
  *buf = 0;
  return buf + 1;
}
