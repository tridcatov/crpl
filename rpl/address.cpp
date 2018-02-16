#include "address.h"
#include "logging.h"

REGISTER_COMPONENT("IP v6 address");

Address Address::getPrivateBroadcastAddress()
{
    Address result;
    result.u8[0] = 0xfc;
    return result;
}

Address::Address()
{
    for ( int i = 0; i < 16; i++)
        u8[i] = 0;
}

void Address::insribeInBuffer(char *buf) const
{
    for (int i = 0; i < length(); i++ )
        buf[i] = u8[i];
}

void Address::readFromBuffer(char *buf)
{
    for (int i = 0; i < length(); i++)
        u8[i] = buf[i];
}

void Address::print() const
{
#if LOGGING_ENABLED == 1
    char buf[16 * 2 + 8 - 1];
    sprintf(buf, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            u8[0], u8[1], u8[2], u8[3], u8[4], u8[5], u8[6], u8[7],
            u8[8], u8[9], u8[10], u8[11], u8[12], u8[13], u8[14], u8[15]);
    DEBUG(buf);
#endif // LOGGING_ENABLED == 1
}

bool Address::operator==(const Address &other) const
{
    for( int i = 0; i < length(); i++) {
        if (u8[i] != other.u8[i] )
            return false;
    }

    return true;
}
