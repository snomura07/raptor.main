#include <print.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

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
    long long total;      // 総メモリ
    long long free;       // 空きメモリ
    long long available;  // 利用可能メモリ
    long long buffers;
    long long cached;
};

CpuInfo getCpuTimes() {
    std::ifstream file("/proc/stat");
    std::string line;
    CpuInfo info = {0, 0, 0, 0, 0, 0, 0, 0};

    if (file.is_open()) {
        std::getline(file, line);
        sscanf(line.c_str(), "cpu %lld %lld %lld %lld %lld %lld %lld %lld",
               &info.user, &info.nice, &info.system, &info.idle,
               &info.iowait, &info.irq, &info.softirq, &info.steal);
    }
    return info;
}

float calculateCpuUsage(const CpuInfo& prev, const CpuInfo& curr) {
    long long prevIdle = prev.idle + prev.iowait;
    long long currIdle = curr.idle + curr.iowait;

    long long prevNonIdle = prev.user + prev.nice + prev.system + prev.irq + prev.softirq + prev.steal;
    long long currNonIdle = curr.user + curr.nice + curr.system + curr.irq + curr.softirq + curr.steal;

    long long prevTotal = prevIdle + prevNonIdle;
    long long currTotal = currIdle + currNonIdle;

    long long totalDiff = currTotal - prevTotal;
    long long idleDiff = currIdle - prevIdle;

    return (float)(totalDiff - idleDiff) / totalDiff * 100.0f;
}



MemInfo getMemInfo() {
    std::ifstream file("/proc/meminfo");
    std::string line;
    MemInfo info = {0, 0, 0, 0, 0};

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.find("MemTotal:") == 0) {
                sscanf(line.c_str(), "MemTotal: %lld kB", &info.total);
            } else if (line.find("MemFree:") == 0) {
                sscanf(line.c_str(), "MemFree: %lld kB", &info.free);
            } else if (line.find("MemAvailable:") == 0) {
                sscanf(line.c_str(), "MemAvailable: %lld kB", &info.available);
            } else if (line.find("Buffers:") == 0) {
                sscanf(line.c_str(), "Buffers: %lld kB", &info.buffers);
            } else if (line.find("Cached:") == 0) {
                sscanf(line.c_str(), "Cached: %lld kB", &info.cached);
            }
        }
    }
    return info;
}

double calculateUsedMemoryGB(const MemInfo& info) {
    // バッファ・キャッシュを除いた実際の使用中メモリを計算（MemTotal - MemFree - Buffers - Cached）
    long long usedMemoryKB = info.total - info.free - info.buffers - info.cached;
    return static_cast<double>(usedMemoryKB) / 1000000.0; // kBをGBに変換
}

int main()
{
    CpuInfo prevCpuInfo = getCpuTimes();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    CpuInfo currCpuInfo = getCpuTimes();
    float cpuUsage = calculateCpuUsage(prevCpuInfo, currCpuInfo);

    MemInfo memInfo = getMemInfo();
    float memUsage = calculateUsedMemoryGB(memInfo);


    print("cpu:", cpuUsage, "%");
    print("memory:", memUsage, "GB");

    return 0;
}
