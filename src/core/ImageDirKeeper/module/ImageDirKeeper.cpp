#include <iostream>
#include <fstream>
#include "ImageDirKeeper.h"
#include <msleep.hpp>
#include <print.hpp>
#include <datetime.hpp>

ImageDirKeeper::ImageDirKeeper():
    files(0)
{
    config.read();

    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

ImageDirKeeper::~ImageDirKeeper(){}

void ImageDirKeeper::run()
{
    while(1){
        scanFiles(config.master.cameraPath);
        removeOldFiles();
        for (const auto& file : files) {
            gprint(file.name, "=>", file.size, "B / ", file.timestamp);
        }
        print("\n");
        msleep(1000);
    }
}

void ImageDirKeeper::scanFiles(const std::string& dirPath)
{
    try {
        files.clear();
        for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                FileInfo fileInfo;
                fileInfo.name      = entry.path().string();
                fileInfo.size      = entry.file_size();
                fileInfo.timestamp = DateTime::fileTimeToUnixTimestamp(entry.last_write_time());

                if(isPng(fileInfo.name)){
                    files.push_back(fileInfo);
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        printe("Filesystem error:", e.what());
    } catch (const std::exception& e) {
        printe("General error:", e.what());
    }

    // 更新時間でソート（古い順）
    std::sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) {
        return std::stol(a.timestamp) < std::stol(b.timestamp);
    });
}

void ImageDirKeeper::removeOldFiles()
{
    while (files.size() > config.sizeThre) {
        try {
            std::filesystem::remove(files.front().name);
            std::cout << "Deleted file: " << files.front().name << std::endl;
            files.erase(files.begin());  // 削除後、リストからも削除
        } catch (const std::filesystem::filesystem_error& e) {
            printe("Failed to delete file:", e.what());
        }
    }
}

bool ImageDirKeeper::isPng(const std::string& fileName) {
    return fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".png";
}
