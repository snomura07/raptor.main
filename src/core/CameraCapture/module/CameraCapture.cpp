#include <iostream>
#include <fstream>
#include "CameraCapture.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <Camera/Camera.h>
// #include <CounterMsg/CounterMsg.pb.h>
#include <msleep.hpp>

CameraCapture::CameraCapture()
{
    this->config.read();

    // base用の設定
    this->modName  = this->config.modName;
    this->commPort = this->config.healthCheckcPort;
    this->runKeepAliveServer();
    this->showActivatedSign();
}

CameraCapture::~CameraCapture(){}

bool CameraCapture::run()
{
    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, this->config.publishTopic);

    Camera camera;

    while(isRunning){

        msleep(1000);
    }

    return isRunning;
}
