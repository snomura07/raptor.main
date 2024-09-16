#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <print.hpp>
#include <msleep.hpp>
#include <str.hpp>
#include "Kernel.h"

Kernel::Kernel()
{
    config.read();

    // base用の設定
    RaptorBase::modName  = config.modName;
    RaptorBase::commPort = config.healthCheckcPort;
    RaptorBase::runKeepAliveServer();
    RaptorBase::showActivatedSign();
    RaptorBase::initLogger();
}

Kernel::~Kernel()
{
    launcher.killAll();

    RaptorBase::logger.writeInfoLog("finish!");
}

bool Kernel::run()
{
    launchProcess();
    processMonitor.healthCheck();

    return true;
}

bool Kernel::launchProcess()
{
    for (const auto& target : config.LaunchProcesses) {
        if(target.launch){
            std::string binPath = config.master.binPath + target.mod;
            launcher.launch(binPath);
        }
    }

    return true;
}
