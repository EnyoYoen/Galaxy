#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Logger
{
public:
    Logger(const char *module);

    static void setup(const std::string& path = std::string());
    static void close();

    Logger& operator<<(const std::string& message);

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    const std::string module;

private:
    void log(const std::string& message);

    static void loop();

    static std::thread logThread;
    static std::mutex *lock;
    static std::condition_variable waiter;
    static std::ofstream out;
    static std::vector<std::string> buffer;
    static bool logging;

    static const char *defaultPath;
};