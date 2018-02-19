#include "dodagconfigurationoption.h"
#include "util.h"

DodagConfigurationOption::DodagConfigurationOption(const RplInstance & i)
    : RplOption(DODAG_CONFIGURATION)
{
    authenticationEnabled = false;

    m_maxRankIncrease = 100;
    m_minHopRankIncrease = 1;
    m_defaultLifetime = 100;
    m_lifetimeUnit = 100;
    m_ocp = 0;
}

static int authorizationFlag = 1 << 3;

DodagConfigurationOption::DodagConfigurationOption(const char *b)
    : RplOption(DODAG_CONFIGURATION)
{
    int flags = b[2];
    authenticationEnabled = flags & authorizationFlag;

    m_maxRankIncrease = Util::shortIntFromBuffer(b + 6);
    m_minHopRankIncrease = Util::shortIntFromBuffer(b + 8);
    m_ocp = Util::shortIntFromBuffer(b + 10);;
    m_defaultLifetime = b[13];
    m_lifetimeUnit = Util::shortIntFromBuffer(b + 14);;
}

char *DodagConfigurationOption::inscribeInBuffer(char * b) const
{
    b[0] = 0x04;
    b[1] = (char) optLength();

    int flags = 0;
    if ( authenticationEnabled ) flags |= authorizationFlag;
    b[2] = flags;
    b[3] = b[4] = b[5] = 0;

    Util::shortIntToBuffer(m_maxRankIncrease, b + 6);
    Util::shortIntToBuffer(m_minHopRankIncrease, b + 8);
    Util::shortIntToBuffer(m_ocp, b + 10);

    b[12] = 0;
    b[13] = (char) m_defaultLifetime;
    Util::shortIntToBuffer(m_lifetimeUnit, b + 14);

    return b + length();

}
