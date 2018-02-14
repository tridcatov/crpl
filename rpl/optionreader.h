#ifndef OPTIONREADER_H
#define OPTIONREADER_H

#include <list>

class RplOption;

class OptionReader
{
public:
    static std::list<RplOption *> readOptions(char * buffer);
    static void writeOptions(std::list<RplOption *> & options, char * buffer);
};

#endif // OPTIONREADER_H
