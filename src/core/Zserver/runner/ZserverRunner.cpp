#include<iostream>
#include "../module/Zserver.h"

int main()
{
    Zserver zserver(5001);
    zserver.run();
}
