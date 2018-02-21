#include "optionreader.h"

#include "rploption.h"
#include "rplpad1option.h"
#include "rplpadnoption.h"
#include "rplsolicitedinformationoption.h"
#include "targetoption.h"
#include "dodagconfigurationoption.h"

#include <stdexcept>

using OptionList = std::list<RplOption *>;
using RE = std::runtime_error;

static RplOption * getOption(const char *buf);

OptionList OptionReader::readOptions(const char *buffer, int length)
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

static RplOption * getOption(const char * buf) {
    switch(*buf) {
    case RplOption::PAD1:
        return new RplPad1Option(buf);
    case RplOption::PADN:
        return new RplPadNOption(buf);
    case RplOption::DODAG_CONFIGURATION:
        return new DodagConfigurationOption(buf);
    case RplOption::RPL_TARGET:
        return new TargetOption(buf);
    case RplOption::SOLICITED_INFORMATION:
        return new RplSolicitedInformationOption(buf);
    default:
        throw new RE("Was unable to parse option");
    }
}
