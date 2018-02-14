#ifndef RPLINSTANCE_H
#define RPLINSTANCE_H

#include <set>
#include "node.h"

class RplInstance {
private:
    int id;
    int version;
    Address dodagid;
public:
    inline int getId() const { return id; }
    inline int getVersion() const { return version; }
    inline const Address & getDID() const { return dodagid; }

    inline void setId(int id) { this->id = id; }
    inline void setVersion(int version) { this->version = version; }
    inline void setDID(const Address & id) { dodagid = id; }
};

#endif // RPLINSTANCE_H
