
class SystemMonitor{
public:
    struct CpuInfo {
        long long user;
        long long nice;
        long long system;
        long long idle;
        long long iowait;
        long long irq;
        long long softirq;
        long long steal;
    };

    struct MemInfo {
        long long total;
        long long free;
        long long available;
        long long buffers;
        long long cached;
    };

public:
    SystemMonitor();
    ~SystemMonitor();

    float getCpuUsage();
    double getUsedMemoryGB();

private:
    CpuInfo getCpuTimes();
    MemInfo getMemInfo();
    float calculateCpuUsage(const CpuInfo& prev, const CpuInfo& curr);
    double calculateUsedMemoryGB(const MemInfo& info);
};
