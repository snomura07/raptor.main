#include <iostream>
#include <fstream>
#include "ImageSaver.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <Camera/Camera.h>
#include <CamMsg/CamMsg.pb.h>
#include <msleep.hpp>

ImageSaver::ImageSaver()
{
    config.read();

    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

ImageSaver::~ImageSaver(){}

bool ImageSaver::run()
{
    int subPort       = config.master.subPort;
    std::string topic = config.subscribeTopic;

    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", subPort , ZmqWrapper::zmqPatternEnum::SUBSCRIBE, topic);

    Camera camera;
    while(isRunning){
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);

        raptor::protobuf::CamMsg protoMsg;
        protoMsg.ParseFromString(msg);

        std::cout << "@" << protoMsg.viewname1() << std::endl;
        std::cout << "img: " << protoMsg.img() << std::endl;
    }

    return isRunning;
}
