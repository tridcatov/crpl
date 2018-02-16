#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

struct Address {
public:
    unsigned char u8[16];
public:
    static Address * fromString(const std::string & s);
    static Address getPrivateBroadcastAddress();
    Address();
    std::string toString() const;
    void print() const;
};

#endif // ADDRESS_H
