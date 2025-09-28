#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>

class Launcher {
public:
    Launcher();
    ~Launcher();
    void launch(const std::string& fileName);
    void waitForAll();
    void killProcess(const std::string& fileName);
    void killAll();

private:
    std::map<std::string, pid_t> programs;
    bool isDevelop;
};
