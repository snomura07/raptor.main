#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class ImageSaver : public RaptorBase{
public:
    ImageSaver();
    ~ImageSaver();
    bool run();

private:
    AppConfig config;
};
