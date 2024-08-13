#include <iostream>
#include <fstream>
#include <string>
#include "CameraCapture.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <Camera/Camera.h>
#include <CamMsg/CamMsg.pb.h>
#include <msleep.hpp>

CameraCapture::CameraCapture()
{
    config.read();

    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

CameraCapture::~CameraCapture(){}

bool CameraCapture::run()
{
    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", config.master.pubPort, ZmqWrapper::zmqPatternEnum::PUBLISH, config.publishTopic);

    Camera camera;
    camera.open();
    while(isRunning){
        camera.capture();
        std::string encodedImage = camera.encode();

        raptor::protobuf::CamMsg cameraMsg;
        cameraMsg.set_viewname1("CameraCapture");
        cameraMsg.set_img(encodedImage);

        std::string sMsg;
        cameraMsg.SerializeToString(&sMsg);
        zmq.sendMessage(sMsg);

        msleep(1000);
    }

    return isRunning;
}
