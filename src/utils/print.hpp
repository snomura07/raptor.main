#ifndef INCLUDED_STR
#define INCLUDED_STR

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

template<typename... Args>
void print(const Args&... args) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y/%m/%d %H:%M:%S");

    ((oss << " " << args), ...);

    std::cout << oss.str() << std::endl;
}

#endif
