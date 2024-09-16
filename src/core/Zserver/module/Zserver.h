#ifndef INCLUDED_ZSERVER
#define INCLUDED_ZSERVER

#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>

class Zserver
{
public:
  Zserver(int port);
  ~Zserver();

  bool run();

  ZmqWrapper zmq;
};

#endif
