#include <iostream>
#include <fstream>
#include "******.h"

******::******()
{
    config.read();

    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

******::~******()
{
    logger.writeInfoLog("finish!");
}

bool ******::run()
{
    bool isRunning = true;
    while(isRunning){
    }

    return isRunning;
}
