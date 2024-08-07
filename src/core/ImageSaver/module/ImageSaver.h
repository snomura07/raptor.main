#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class ImageSaver : public RaptorBase{
public:
    ImageSaver();
    ~ImageSaver();
    bool run();

private:
    void receiveMsg(std::string msg, std::string topic);

private:
    AppConfig config;
};
