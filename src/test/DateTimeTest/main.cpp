#include <iostream>
#include <print.hpp>
#include <datetime.hpp>

int main() {
    print(DateTime::getFormattedDateTime(), ",", DateTime::getCompactDateTime());

    print("test", "ok", "ggg");
    print("another", "message", "here");
    print("another", "message", "here", 123);
    return 0;
}
