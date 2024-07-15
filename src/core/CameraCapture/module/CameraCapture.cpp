#include <iostream>
#include <fstream>
#include "CameraCapture.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <Camera/Camera.h>
#include <CamMsg/CamMsg.pb.h>
#include <msleep.hpp>

CameraCapture::CameraCapture()
{
    this->config.read();

    // base用の設定
    this->modName  = this->config.modName;
    this->commPort = this->config.healthCheckcPort;
    this->runKeepAliveServer();
    this->showActivatedSign();
    this->initLogger();
}

CameraCapture::~CameraCapture(){}

bool CameraCapture::run()
{
    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, this->config.publishTopic);

    Camera camera;
    while(isRunning){
        camera.capture();

        raptor::protobuf::CamMsg camMsg;
        cameraMsg.set_viewname1("CameraCapture");
        cameraMsg.set_image(camera.encode());

        std::string sMsg;
        cameraMsg.SerializeToString(&sMsg);
        zmq.sendMessage(sMsg);
        logger.writeInfoLog("data: " + frame);

        msleep(1000);
    }

    return isRunning;
}
