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
    Address(const Address & other);
    std::string toString() const;

    void insribeInBuffer(char * buf) const;
    void readFromBuffer(const char * buf);

    void print() const;
    inline int length() const { return 16; }
    bool operator==(const Address & other) const;
    bool operator<(const Address & other) const;
    void operator=(const Address & other);
};

#endif // ADDRESS_H
