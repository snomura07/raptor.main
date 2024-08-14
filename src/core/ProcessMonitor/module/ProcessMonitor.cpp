#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <print.hpp>
#include <msleep.hpp>
#include "ProcessMonitor.h"

ProcessMonitor::ProcessMonitor()
{
    config.read();

    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

ProcessMonitor::~ProcessMonitor()
{
    logger.writeInfoLog("finish!");
}

bool ProcessMonitor::run()
{
    for (const auto& confPath : confSummary.jsonList) {
        ProcessInfo process(confPath);
        processMap[process.modName] = std::make_shared<ProcessInfo>(process);
    }

    bool isRunning = true;
    while(isRunning){
        for (const auto& pair : processMap) {
            pair.second->checkAlive();
            print("Key:", pair.first, "=>", pair.second->isActive());
        }

        print();
        msleep(1000);
    }

    return isRunning;
}
