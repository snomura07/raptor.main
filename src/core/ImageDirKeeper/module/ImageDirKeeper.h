#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class ImageDirKeeper : public RaptorBase{
public:
    struct FileInfo {
        std::string name;
        std::uintmax_t size;
        std::string timestamp;
    };

public:
    ImageDirKeeper();
    ~ImageDirKeeper();
    void run();

private:
    void scanFiles(const std::string& dirPath);
    void removeOldFiles();
    bool isPng(const std::string& fileName);

private:
    AppConfig config;
    std::vector<FileInfo> files;
};
