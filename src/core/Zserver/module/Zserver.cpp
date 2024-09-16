#include <iostream>
#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>
#include <print.hpp>
#include "Zserver.h"
#include "Gateway.h"
#include "Zdata.h"

Zserver::Zserver(int port)
{
  zmq.registerSession("*", port, ZmqWrapper::zmqPatternEnum::REPLY, "ZSERVER");
}

Zserver::~Zserver(){}

bool Zserver::run()
{
  Gateway gateway;
  bool isRunning = true;

  while(isRunning){
    std::string request = "";
    zmq.pollMessage(request, -1);

    Zdata zdata(request);
    print("main command: ", zdata.mainCommand);
    print("optVal: ");
    for (const auto& value : zdata.optValues) {
        print("->", value);
    }
    print("optStr: ");
    for (const auto& value : zdata.optStrings) {
        print("->", value);
    }
    print("");

    std::string rmsg = gateway.routeRequest(zdata.mainCommand, zdata.optValues, zdata.optStrings);
    zmq.sendMessage(rmsg);
  }

  return isRunning;
}