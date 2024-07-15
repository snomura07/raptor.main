#include "Logger.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger(){}
Logger::~Logger(){
    ofs.close();
}

void Logger::init(std::string name){
    std::string fileName = name + ".log";
    std::string filePath = "/usr/local/log/" + fileName;
    ofs.open(filePath, std::ios::app);
}

void Logger::writeInfoLog(std::string msg){
    writeLog("info", msg);
}

void Logger::writeErrorLog(std::string msg){
    writeLog("error", msg);
}

void Logger::writeLog(std::string level, std::string msg){
    ofs << getTime();
    ofs << " [" << level << "] : " << msg << std::endl;
}

std::string Logger::getTime(){
    std::time_t now = std::time(nullptr);
    std::tm tm_now = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm_now, "%Y/%m/%d %H:%M:%S");
    return oss.str();
}
