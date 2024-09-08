#include "Launcher.h"
#include <unistd.h>    // fork, execvp, kill
#include <sys/wait.h>  // waitpid
#include <signal.h>    // kill関数用
#include <Env/Env.h>

Launcher::Launcher()
{
    isDevelop = isDevEnv();
}

Launcher::~Launcher(){}

void Launcher::launch(const std::string& fileName)
{
    pid_t pid = fork();


    if (pid == -1) {
        std::cerr << "Failed to fork for program: " << fileName << std::endl;
    } else if (pid == 0) {
        if(isDevelop){
            char *args[] = {(char *)"qemu-arm", (char *)"-L", (char *)"/usr/arm-linux-gnueabi", (char *)fileName.c_str(), (char *)NULL};
            execvp(args[0], args);
        }
        else{
            char *args[] = {(char *)fileName.c_str(), (char *)NULL};
            execvp(args[0], args);
        }

        std::cerr << "Failed to execute program: " << fileName << std::endl;
        exit(1);
    } else {
        programs[fileName] = pid;
        std::cout << "Launched program: " << fileName << " with PID " << pid << std::endl;
    }
}

void Launcher::waitForAll()
{
    for (const auto& entry : programs) {
        int status;
        waitpid(entry.second, &status, 0);
        if (WIFEXITED(status)) {
            std::cout << "Program " << entry.first << " exited with status " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cout << "Program " << entry.first << " terminated abnormally." << std::endl;
        }
    }
}

void Launcher::killProcess(const std::string& fileName)
{
    auto it = programs.find(fileName);
    if (it != programs.end()) {
        pid_t pid = it->second;
        if (kill(pid, SIGTERM) == 0) {
            std::cout << "Program " << fileName << " (PID: " << pid << ") was killed." << std::endl;
        } else {
            std::cerr << "Failed to kill program: " << fileName << std::endl;
        }
    } else {
        std::cerr << "Program " << fileName << " not found." << std::endl;
    }
}

void Launcher::killAll()
{
    for (const auto& entry : programs) {
        pid_t pid = entry.second;
        if (kill(pid, SIGTERM) == 0) { // SIGTERMでプロセスを終了させる
            std::cout << "Program " << entry.first << " (PID: " << pid << ") was killed." << std::endl;
        } else {
            std::cerr << "Failed to kill program: " << entry.first << std::endl;
        }
    }
    programs.clear(); // プログラムのリストをクリア
}
