#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class CameraCapture : public RaptorBase{
public:
    CameraCapture();
    ~CameraCapture();
    bool run();

private:
    AppConfig config;
};
