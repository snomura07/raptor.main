#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <memory>
#include <ZmqWrapper/ZmqWrapper.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(int argc, char **argv)
{
    std::ifstream inputFile("/opt/raptor/config/ConfSummary");
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file: /opt/raptor/config/ConfSummary" << std::endl;
        return 1;
    }

    std::string filePath;
    std::map<std::string, std::shared_ptr<ZmqWrapper>> clientMap;
    while (std::getline(inputFile, filePath)) {
        std::ifstream jsonFile(filePath);
        if (!jsonFile.is_open()) {
            std::cerr << "Could not open the file: " << filePath << std::endl;
            continue;
        }

        json jsonData;
        jsonFile >> jsonData;
        std::string modName = jsonData["modName"];
        int port            = jsonData["healthCheckPort"];
        std::cout << modName << " : " << port << std::endl;

        std::shared_ptr<ZmqWrapper> zmq = std::make_shared<ZmqWrapper>();
        zmq->registerSession("127.0.0.1", port, ZmqWrapper::zmqPatternEnum::REQUEST, "HELTHCHECK");
        clientMap[modName] = zmq;
    }

    while(1){
        for (const auto& pair : clientMap) {
            const std::string& modName = pair.first;
            const std::shared_ptr<ZmqWrapper>& zmq = pair.second;

            std::cout << modName << " check... ";
            zmq->sendMessage("ggg");
            std::string rmsg = "";
            auto res = zmq->pollMessage(rmsg, 10);
            if(res < 0){
                std::cout << " isDead!!!!!!!!!!!!!!! " << std::endl;
            }
            else{
                std::cout << " alive!! " << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
