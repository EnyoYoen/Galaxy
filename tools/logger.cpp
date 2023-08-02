#include "logger.h"

#include <fstream>

#include <QDebug>

#ifndef NDEBUG
#include <iostream>
#endif

std::thread Logger::logThread;
std::mutex *Logger::lock;
std::condition_variable Logger::waiter;
std::ofstream Logger::out;
std::vector<std::string> Logger::buffer;
bool Logger::logging = true;

const char *Logger::defaultPath = "log.txt";

Logger::Logger(const char *m_module)
    : module(m_module)
{}

void Logger::setup(const std::string& path)
{
    logThread = std::thread(&Logger::loop);
    out.open(path.empty() ? defaultPath : path);
    lock = new std::mutex();
}

void Logger::close()
{
    logging = false;
    if (!buffer.empty()) {
        lock->lock();
        buffer.clear();
        lock->unlock();
    }
    qDebug() << "d";
    try {
        waiter.notify_one();
        logThread.join();
        out.close();
    } catch (std::system_error e) {
        qDebug() << e.what() << e.code().value();
    }
}

Logger& Logger::operator<<(const std::string& message) {
    info(message);
    return *this;
}

void Logger::info(const std::string& message)     { log("INFO (" + module + ") " + message); }
void Logger::warn(const std::string& message)     { log("WARN (" + module + ") " + message); }
void Logger::error(const std::string& message)    { log("ERROR (" + module + ") " + message); }
void Logger::critical(const std::string& message) { log("CRITICAL (" + module + ") " + message); }

void Logger::log(const std::string& message)
{
    if (logging) {
        lock->lock();
        buffer.push_back(message);
        lock->unlock();
        qDebug() << "a";
        waiter.notify_one();
    }
}

void Logger::loop()
{
    while (logging) {
        while (!buffer.empty()) {
#ifndef NDEBUG
            std::cout << buffer.front() << std::endl;
#endif
            out << buffer.front() << std::endl;
            lock->lock();
            buffer.erase(buffer.begin());
            lock->unlock();
        }
        qDebug() << "b";
        std::unique_lock<std::mutex> lk(*lock);
        waiter.wait(lk);
        lk.unlock();
        qDebug() << "c";
    }
}