#include "logger.h"

#include <fstream>
#include <filesystem>

#ifndef NDEBUG
#include <iostream>
#endif

std::string Logger::defaultPath = "log.txt";

Logger::Logger(const char *m_module)
    : module(m_module)
{
#ifdef DL
    out.open("cache/" + module + "_" + defaultPath, std::ofstream::out | std::ofstream::app);
#else
    out.open(defaultPath, std::ofstream::out | std::ofstream::app);
#endif
}

Logger::Logger(const char *m_module, const std::string& path)
    : module(m_module)
{
    out.open(path.empty() ? defaultPath : path);
}

Logger::Logger(const std::string& m_module)
    : module(m_module)
{
    out.open(defaultPath);
}

Logger::Logger(const std::string& m_module, const std::string& path)
    : module(m_module)
{
    out.open(path.empty() ? defaultPath : path);
}

void Logger::log(const std::string& message)
{
#ifndef NDEBUG
    std::cout << message << std::endl;
#endif
    out << message << std::endl;
}

void Logger::operator<<(const std::string& message) { info(message); }

void Logger::info(const std::string& message)     { log("[INFO] (" + module + ") " + message); }
void Logger::warn(const std::string& message)     { log("[WARN] (" + module + ") " + message); }
void Logger::error(const std::string& message)    { log("[ERROR] (" + module + ") " + message); }
void Logger::critical(const std::string& message) { log("[CRITICAL] (" + module + ") " + message); }
