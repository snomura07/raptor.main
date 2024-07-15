#include <iostream>
#include <Logger/Logger.h>
int main()
{
    Logger logger;
    logger.init("test");
    logger.writeInfoLog("start");
    logger.writeInfoLog("起動");
    logger.writeErrorLog("failed");
}
