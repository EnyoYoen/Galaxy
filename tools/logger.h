#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Logger
{
public:
    Logger(const char *module);
    Logger(const char *module, const std::string& path);
    Logger(const std::string& module);
    Logger(const std::string& module, const std::string& path);

    void operator<<(const std::string& message);

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    const std::string module;

private:
    void log(const std::string& message);

    std::vector<std::string> buffer; // TODO : buffer used by a thread which write to the file (no long io operation blocking <- need to benchmark to see if there is a difference) 
    std::ofstream out;  

    static std::string defaultPath;
};