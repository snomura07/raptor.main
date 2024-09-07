#include <iostream>
#include <fstream>
#include <print.hpp>
#include "ConfSummary.h"

ConfSummary::ConfSummary()
{
    masterConf.read();

    std::ifstream file(masterConf.configPath+"ConfSummary");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            jsonList.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "ファイルを開くことができませんでした。" << std::endl;
    }
}

ConfSummary::~ConfSummary(){}

void ConfSummary::show()
{
    for (const auto& path : jsonList) {
        print(path);
    }
}
