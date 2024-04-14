#include <iostream>
#include <string>
#include <ZmqWrapper/ZmqWrapper.h>
#include "Zserver.h"
#include "Gateway.h"

Zserver::Zserver(int port)
{
  this->zmq.registerSession("*", port, ZmqWrapper::zmqPatternEnum::REPLY, "ZSERVER");
}

Zserver::~Zserver(){}

bool Zserver::run()
{
  Gateway gateway;
  bool isRunning = true;

  while(isRunning){
    std::string request = "";
    this->zmq.pollMessage(request, -1);

    std::string rmsg = gateway.routeRequest(request);
    this->zmq.sendMessage("Accept!");

    // if(!request.empty()){
    //   std::cout << request << std::endl;
    //   if(request == "STOP"){
    //     isRunning = false;
    //   }
    //   this->zmq.sendMessage("Accept!");
    // }
  }

  return isRunning;
}


Zclient::Zclient(int port)
{
  this->zmq.registerSession("127.0.0.1", port, ZmqWrapper::zmqPatternEnum::REQUEST, "ZSERVER");
}

Zclient::~Zclient(){}

std::string Zclient::run(std::string msg)
{
  this->zmq.sendMessage(msg);

  std::string rmsg = "";
  auto res = this->zmq.pollMessage(rmsg, 1000);
  std::cout << "received: " << rmsg << std::endl;

  return rmsg;
}
