#include <iostream>
#include <fstream>
#include "ImageSaver.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <CamMsg/CamMsg.pb.h>
#include <msleep.hpp>
#include <datetime.hpp>
#include <print.hpp>
#include <Image/Image.h>

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
    std::string ip    = config.master.getStringFromMap(config.clientIp);
    int subPort       = config.master.subPort;
    std::string topic = config.subscribeTopic;

    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession(ip, subPort , ZmqWrapper::zmqPatternEnum::SUBSCRIBE, topic, std::bind(&ImageSaver::receiveMsg, this, std::placeholders::_1, std::placeholders::_1));

    while(isRunning){
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);
    }

    return isRunning;
}

void ImageSaver::receiveMsg(std::string msg, std::string topic)
{
    raptor::protobuf::CamMsg protoMsg;
    protoMsg.ParseFromString(msg);
    print(protoMsg.viewname1(), "img size:", protoMsg.img().size());

    Image image;
    image.readFromBinary(protoMsg.img());
    image.setTime();

    std::string imagePath = config.master.cameraPath + DateTime::getCompactDateTime() + ".png";
    image.saveAsPng(imagePath);
}
