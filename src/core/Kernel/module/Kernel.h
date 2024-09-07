#include <string>
#include <memory>
#include <unordered_map>
#include <RaptorBase/RaptorBase.h>
#include <InfoChat/InfoChat.h>
#include "../config/AppConfig.h"
#include "ConfSummary.h"
#include "ProcessInfo.h"
#include "Launcher.h"

class Kernel : public RaptorBase{
public:
    Kernel();
    ~Kernel();
    bool launchProcess();

    bool healthCheck();
    // プロセスの起動、ヘルスチェック
    // CPU, メモリなど資源管理

private:
    InfoChat infoChat;
    AppConfig config;
    ConfSummary confSummary;
    Launcher launcher;
    std::unordered_map<std::string, std::shared_ptr<ProcessInfo>> processMap;
};
