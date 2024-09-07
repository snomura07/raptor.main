#include<iostream>
#include "../module/Kernel.h"

int main(int argc, char *argv[])
{
    Kernel kernel;
    kernel.launchProcess();
    kernel.healthCheck();
    return 0;
}
