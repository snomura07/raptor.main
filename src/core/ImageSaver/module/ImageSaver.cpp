#include <iostream>
#include <fstream>
#include "ImageSaver.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <CamMsg/CamMsg.pb.h>
#include <msleep.hpp>
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
    int subPort       = config.master.subPort;
    std::string topic = config.subscribeTopic;

    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", subPort , ZmqWrapper::zmqPatternEnum::SUBSCRIBE, topic, std::bind(&ImageSaver::receiveMsg, this, std::placeholders::_1, std::placeholders::_1));

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
    std::cout << topic << " " << protoMsg.viewname1() << std::endl;

    std::string imgs = protoMsg.img();
    std::cout << imgs.size() << std::endl;

    Image image;
    image.readFromBinary(protoMsg.img());
    image.setTime();

    std::string imagePath = config.master.imagePath + "/mmm.png";
    image.saveAsPng(imagePath);
}
