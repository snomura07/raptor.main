#include <iostream>
#include "/usr/local/include/pigpio.h"
#include "/usr/local/include/zmq.h"

int main()
{
    void* context = zmq_ctx_new();
    if( gpioInitialise() >= 0 ){
        std::cout << "OK!" << std::endl;
    }
    else{
        std::cout << "NG.." << std::endl;
    }
    return 0;
}
