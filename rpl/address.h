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

    void insribeInBuffer(char * buf) const;
    void readFromBuffer(char * buf);

    void print() const;
    inline int length() const { return 16; }
    bool operator==(const Address & other) const;
};

#endif // ADDRESS_H
