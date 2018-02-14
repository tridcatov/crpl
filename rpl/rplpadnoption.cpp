#include "rplpadnoption.h"

#include <stdexcept>

using RE = std::runtime_error;

RplPadNOption::RplPadNOption(int padding)
    : RplOption(RplOption::PADN)
{
    if ( padding < 2 || padding > 7 )
        throw new RE("Not allowed padding out of constraints [2, 7]");

    this->padding = padding;
}

char * RplPadNOption::inscribeInBuffer(char *buf) const
{
    buf[0] = 0x01;
    buf[1] = (char)padding - 2;
    for( int i = 2; i < padding; i++) {
        buf[i] = 0x00;
    }
    return buf + padding;
}
