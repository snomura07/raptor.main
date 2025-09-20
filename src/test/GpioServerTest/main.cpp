#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ZmqWrapper/ZmqWrapper.h>
#include <GpioServerMsg/GpioServerMsg.pb.h>

int main(int argc, char **argv)
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, "GpioServer");

    {
        raptor::protobuf::GpioServerMsg protoMsg;
        protoMsg.set_type(raptor::protobuf::GpioServerMsg::CH_OUTPUT);
        protoMsg.set_port(17);

        std::string msg;
        protoMsg.SerializeToString(&msg);
        for(int i=0; i<2; i++){
            zmq.sendMessage(msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    {
        raptor::protobuf::GpioServerMsg protoMsg;
        protoMsg.set_type(raptor::protobuf::GpioServerMsg::SET_HIGH);
        protoMsg.set_port(17);

        std::string msg;
        protoMsg.SerializeToString(&msg);
        for(int i=0; i<2; i++){
            zmq.sendMessage(msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }


    return 0;
}
