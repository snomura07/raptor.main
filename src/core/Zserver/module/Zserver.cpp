#include <iostream>
#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>
#include <ZserverMsg/ZserverMsg.pb.h>
#include "Zserver.h"
#include "Gateway.h"


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

    raptor::protobuf::ZserverMsg zserverMsg;
    zserverMsg.ParseFromString(request);
    std::string path = zserverMsg.path();
    std::vector<int> params(zserverMsg.params().begin(), zserverMsg.params().end());

    std::cout << path << " " << (params.size() > 0 ? params.front() : -1) << std::endl;

    std::string rmsg = gateway.routeRequest(path, params);
    zmq.sendMessage(rmsg);
  }

  return isRunning;
}


Zclient::Zclient(int port)
{
  zmq.registerSession("127.0.0.1", port, ZmqWrapper::zmqPatternEnum::REQUEST, "ZSERVER");
}

Zclient::~Zclient(){}

std::string Zclient::run(std::string path, std::vector<int> params)
{
  raptor::protobuf::ZserverMsg zserverMsg;
  zserverMsg.set_path(path);
  for (int param : params) {
    zserverMsg.add_params(param);
  }
  std::string serializedMsg;
  zserverMsg.SerializeToString(&serializedMsg);
  zmq.sendMessage(serializedMsg);

  std::string rmsg = "";
  auto res = zmq.pollMessage(rmsg, -1);
  std::cout << "received: " << rmsg << std::endl;

  return rmsg;
}
