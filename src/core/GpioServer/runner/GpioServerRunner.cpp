#include<iostream>
#include "../module/GpioServer.h"

int main(int argc, char *argv[])
{
    GpioServer gpioServer;
    gpioServer.run();
    return 0;
}
