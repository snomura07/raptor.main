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
    RaptorBase::init(config.modName, config.healthCheckPort);

    // launch対象のモジュールをリスト化
    for (const auto& confPath : confSummary.jsonList) {
        ProcessInfo process(confPath);
        processMap[process.modName] = std::make_shared<ProcessInfo>(process);
        processMap[process.modName]->init();
    }

    // shutdown用の設定
    shutdownGate.setReceiveGate();
}

Kernel::~Kernel()
{
    launcher.killAll();

    RaptorBase::logger.writeInfoLog("finish!");
}

bool Kernel::run()
{
    launchProcess();

    while (true)
    {
        healthCheckProcess();

        if(checkShutdownCommand()){
            logger.writeInfoLog("shutdown command received");
            shutdownProcess();
        }
    }


    return true;
}

bool Kernel::launchProcess()
{
    for (const auto& target : config.LaunchProcesses) {
        if(target.launch){
            std::string binPath = strJoin(config.master.binPath, target.mod);
            print("Launching process: " + binPath);
            launcher.launch(binPath);

            auto it = processMap.find(target.mod);
            if (it != processMap.end()) {
                it->second->state = ProcessInfo::RUNNING;
            }
        }
    }

    return true;
}

bool Kernel::healthCheckProcess()
{
    for (const auto& process : config.LaunchProcesses) {
        if (!process.launch){
            // 起動対象じゃないものはスキップ
            continue;
        }

        // check process status
        auto it = processMap.find(process.mod);
        it->second->checkAlive();
        if (!it->second->isModified()){
            // 状態に変化がなければスキップ
            continue;
        }

        if (it->second->isAlive()) {
            logger.writeInfoLog(strJoin(process.mod, " が起動しました。"));
        } else {
            logger.writeInfoLog(strJoin(process.mod, " が停止しました。"));
        }
    }

    return true;
}

bool Kernel::checkShutdownCommand()
{
    if(shutdownGate.isSignalReceived()){
        return false;
    }

    return shutdownGate.checkSignal();
}

bool Kernel::shutdownProcess()
{
    for (const auto& process : config.LaunchProcesses) {
        if (!process.launch){
            // 起動対象じゃないものはスキップ
            continue;
        }

        // check process status
        auto it = processMap.find(process.mod);
        it->second->shutdown();
    }

    return true;
}
