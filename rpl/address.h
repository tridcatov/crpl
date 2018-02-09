#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

struct Address {
public:
    char u8[16];
public:
    static Address * fromString(const std::string & s);
    std::string toString() const;
};

#endif // ADDRESS_H
