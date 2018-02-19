#ifndef DODAGCONFIGURATIONOPTION_H
#define DODAGCONFIGURATIONOPTION_H

#include "rploption.h"

class RplInstance;

class DodagConfigurationOption : public RplOption
{
private:
    inline int optLength() const { return 14; }
    bool authenticationEnabled;
    int m_ocp;
    int m_lifetimeUnit;
    int m_defaultLifetime;
    int m_maxRankIncrease;
    int m_minHopRankIncrease;
public:
    DodagConfigurationOption(const RplInstance &);
    DodagConfigurationOption(const char * buf);
    virtual ~DodagConfigurationOption() {}

    virtual int length() const { return optLength() + 2; }
    virtual char * inscribeInBuffer(char *buf) const;

    inline bool isAuthenticationEnabled() const { return authenticationEnabled; }

    inline int lifetimeUnit() const { return  m_lifetimeUnit; }
    inline int defaultLifetime() const { return m_defaultLifetime; }
    inline int ocp() const { return m_ocp; }
    inline int maxRankIncrease() const { return m_maxRankIncrease; }
    inline int minHopRankIncrease() const { return m_maxRankIncrease; }
};

#endif // DODAGCONFIGURATIONOPTION_H
