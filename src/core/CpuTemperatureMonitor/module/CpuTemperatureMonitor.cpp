#include <iostream>
#include <fstream>
#include "CpuTemperatureMonitor.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <CpuTemperatureMsg/CpuTemperatureMsg.pb.h>
#include <Env/Env.h>
#include <msleep.hpp>

CpuTemperatureMonitor::CpuTemperatureMonitor()
{
    this->config.read();

    // base用の設定
    this->modName  = this->config.modName;
    this->commPort = this->config.healthCheckcPort;
    this->runKeepAliveServer();

    // 開発環境では仮の温度ファイルを読み込む
    if(isDevEnv()){
        this->tempFilePath = "/home/nomura/thermal_zone0/temp";
    }
    else{
        this->tempFilePath = "/sys/class/thermal/thermal_zone0/temp";
    }
}

CpuTemperatureMonitor::~CpuTemperatureMonitor(){}

bool CpuTemperatureMonitor::run()
{
    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, this->config.publishTopic);

    while(isRunning){
        double cpuTemperature = this->getTemperature();

        raptor::protobuf::CpuTemperatureMsg cpuTemperatureMsg;
        cpuTemperatureMsg.set_viewname1("cpuTemp");
        cpuTemperatureMsg.set_cputemperature(cpuTemperature);

        std::string sMsg;
        cpuTemperatureMsg.SerializeToString(&sMsg);
        zmq.sendMessage(sMsg);

        msleep(1000);
    }

    return isRunning;
}

double CpuTemperatureMonitor::getTemperature()
{
    std::ifstream file(this->tempFilePath);
    if (!file) {
        std::cerr << "Error opening CPU temperature file" << std::endl;
        return -255.0;
    }

    double temperature;
    file >> temperature;
    file.close();

    // toセルシウス
    return temperature / 1000.0f;
}
