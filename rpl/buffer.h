#ifndef BUFFER_H
#define BUFFER_H

#define MAX_BUF_LEN 512 * 4
namespace rpl {

class Buffer
{
public:
  int len;
  char buf[MAX_BUF_LEN];
  void printHex() const;
};

}
#endif // BUFFER_H
