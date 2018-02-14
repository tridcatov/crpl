#include "optionreader.h"

#include "rploption.h"
#include "rplpad1option.h"
#include "rplpadnoption.h"
#include "rplsolicitedinformationoption.h"
#include "logging.h"

#include <stdexcept>

using OptionList = std::list<RplOption *>;
using RE = std::runtime_error;

static RplOption * getOption(char *buf);

REGISTER_COMPONENT("OptionReader");

OptionList OptionReader::readOptions(char *buffer, int length)
{
    OptionList result;
    int optLength = 0;
    while ( optLength < length ) {
        RplOption * option = getOption(buffer + optLength);
        result.push_back(option);
        optLength += option->length();
    }

    return result;
}

static RplOption * getOption(char * buf) {
    switch(*buf) {
    case RplOption::PAD1:
        return new RplPad1Option(buf);
    case RplOption::PADN:
        return new RplPadNOption(buf);
    case RplOption::SOLICITED_INFORMATION:
        return new RplSolicitedInformationOption(buf);
    default:
        throw new RE("Was unable to parse option");
    }
}
