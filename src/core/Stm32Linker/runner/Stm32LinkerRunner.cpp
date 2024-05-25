#include<iostream>
#include "../module/Stm32Linker.h"

int main(int argc, char *argv[])
{
    Stm32Linker stm32Linker;
    if(!stm32Linker.init()){
        return 0;
    }

    stm32Linker.run();
    return 0;
}
