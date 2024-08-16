#include <iostream>
#include <fstream>
#include "ChatServer.h"

ChatServer::ChatServer()
{
    config.read();

    // base用の設定
    RaptorBase::modName  = config.modName;
    RaptorBase::commPort = config.healthCheckcPort;
    RaptorBase::runKeepAliveServer();
    RaptorBase::showActivatedSign();
    RaptorBase::initLogger();
}

ChatServer::~ChatServer()
{
    RaptorBase::logger.writeInfoLog("finish!");
}

bool ChatServer::run()
{
    bool isRunning = true;
    while(isRunning){
    }

    return isRunning;
}
