#ifndef INCLUDED_ZSERVER
#define INCLUDED_ZSERVER

#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class Zserver : public RaptorBase
{
public:
  Zserver();
  ~Zserver();

  bool run();

public:
  ZmqWrapper zmq;

private:
  AppConfig config;

};

#endif
