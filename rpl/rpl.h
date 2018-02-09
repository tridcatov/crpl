#ifndef RPL_H
#define RPL_H

class RplInstance;
class IOAgent;

class Rpl {
private:
    RplInstance * insstance;
    IOAgent * io;
public:
    Rpl(IOAgent * io);
};

#endif // RPL_H
