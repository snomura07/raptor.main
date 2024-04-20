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

class Zclient
{
public:
  Zclient(int port);
  ~Zclient();

  std::string run(std::string path, std::vector<int> params);

  ZmqWrapper zmq;
};

#endif
