#include "Logger.hpp"

Logger::Logger(std::string filename)
{    
    try
    {
        logfile.open(filename, std::ios_base::in | std::ios_base::out | std::ios::app);        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
    
}
Logger::~Logger()
{
    if(logfile.is_open())
    {
        logfile.close();
    }
}

void Logger::readLog()
{
    logfile.seekp(0);
    std::vector<std::string> loglines;
    std::string line;
    if (logfile.is_open())
    {
        while (getline(logfile, line))
        {
            std::cout << line << std::endl;
            loglines.push_back(line);
        }
        
    }
}

void Logger::writeLog(std::string event)
{
    logfile.seekg(0, std::ios::end);
    if (logfile.is_open())
    {
        logfile << event;
    }
}
