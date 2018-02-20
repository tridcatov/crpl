#ifndef UTIL_H
#define UTIL_H


class Util
{
public:
    inline static short int shortIntFromBuffer(const char * b) {
        return shortIntFromBuffer((const unsigned char *)b);
    }

    inline static short int shortIntFromBuffer(const unsigned char * b) {
        return (b[0] << 8) | b[1];
    }

    inline static void shortIntToBuffer(short int i, char * b) {
        shorintToBuffer(i, (unsigned char *)b);
    }

    inline static void shorintToBuffer(short int i, unsigned char * b) {
        b[0] = i >> 8;
        b[1] = i & 0xff;
    }
};

#endif // UTIL_H
