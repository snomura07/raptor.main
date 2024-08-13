#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class Counter : public RaptorBase{
public:
    Counter();
    ~Counter();
    bool run();

private:
    AppConfig config;
    unsigned long count;
};
