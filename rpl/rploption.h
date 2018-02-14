#ifndef RPLOPTION_H
#define RPLOPTION_H


class RplOption
{
    friend class OptionReader;
public:
    enum Type {
        PAD1 = 0,
        PADN = 1,
        SOLICITED_INFORMATION = 7
    };
private:
    RplOption() {}
protected:
    Type type;
    RplOption(Type type) : type(type) {}
public:
    virtual char * inscribeInBuffer(char * buf) const = 0;
    virtual ~RplOption() {}
    // virtual char * readOption(char * buf) = 0;
    virtual int length() const = 0;
    inline Type getType() { return type; }

};

#endif // RPLOPTION_H
