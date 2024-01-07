#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Logger
{
    public:
        Logger(std::string filename);
        ~Logger();
        void readLog();
        void writeLog(std::string event);
    private:
        std::fstream logfile;
};