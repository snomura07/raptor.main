#include "ProcessMonitor.h"
#include <print.hpp>
#include <msleep.hpp>
#include <str.hpp>

ProcessMonitor::ProcessMonitor()
{
    config.read();   
}
ProcessMonitor::~ProcessMonitor(){}

void ProcessMonitor::healthCheck()
{
    for (const auto& confPath : confSummary.jsonList) {
        ProcessInfo process(confPath);
        processMap[process.modName] = std::make_shared<ProcessInfo>(process);
        processMap[process.modName]->init();
    }

    bool isRunning = true;
    while(isRunning){
        nlohmann::json processStatus;
        for (const auto& process : config.LaunchProcesses) {
            if (!process.launch){
                // 起動対象じゃないものはここでfalseに
                processStatus[process.mod] = false;
                continue;
            } 

            // check process status
            auto it = processMap.find(process.mod);
            it->second->checkAlive();
            processStatus[process.mod] = it->second->isAlive();
            if (!it->second->isModified()){
                continue;
            }

            // send chat 
            if (it->second->isAlive()) {
                infoChat.sendInfoMsg(config.modName, strJoin(process.mod, " が起動しました。"));
            } else {
                infoChat.sendErrorMsg(config.modName, strJoin(process.mod, " が停止しました。"));
            }
        }
        std::string statusJson = processStatus.dump(4);
        print("プロセス状態:\n", statusJson);


        // print("");
        msleep(1000);
    }
}
