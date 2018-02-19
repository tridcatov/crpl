#ifndef UTIL_H
#define UTIL_H


class Util
{
public:
    inline static short int shortIntFromBuffer(const char * b) {
        return b[0] << 7 | b[1];
    }

    inline static void shortIntToBuffer(short int i, char * b) {
        b[0] = i >> 7;
        b[1] = i & 0xff;
    }
};

#endif // UTIL_H
