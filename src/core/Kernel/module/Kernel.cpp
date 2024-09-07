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

bool Kernel::launchProcess()
{
    for (const auto& target : config.LaunchProcesses) {
        std::string binPath = config.master.binPath + target.mod;
        launcher.launch(binPath);
    }

    return true;
}

bool Kernel::healthCheck()
{
    for (const auto& confPath : confSummary.jsonList) {
        ProcessInfo process(confPath);
        auto it = std::find_if(config.LaunchProcesses.begin(), config.LaunchProcesses.end(),
                            [&process](const AppConfig::Process& p) {
                                return p.mod == process.modName;
                            });

        if (it != config.LaunchProcesses.end()) {
            processMap[process.modName] = std::make_shared<ProcessInfo>(process);
            processMap[process.modName]->init();
        }
    }

    bool isRunning = true;
    while(isRunning){
        for (const auto& pair : processMap) {
            pair.second->checkAlive();
            // 表示
            // print("Key:", pair.first, "=>", pair.second->isAlive());

            if(pair.second->isModified()){
                if(pair.second->isAlive()){
                    // wakeup
                    infoChat.sendInfoMsg(config.modName, strJoin(pair.first, " が起動しました。"));
                }
                else{
                    // dead
                    infoChat.sendErrorMsg(config.modName, strJoin(pair.first, " が停止しました。"));
                }
            }
        }
        // print();
        msleep(1000);
    }

    return isRunning;
}
