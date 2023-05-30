#ifndef PROJECT_KFLOG_H
#define PROJECT_KFLOG_H

#include "YJJ_DECLARE.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#define KF_LOG_FATAL(kfLogger, content) LOG4CPLUS_FATAL(kfLogger->getLogger(), content)
#define KF_LOG_ERROR(kfLogger, content) LOG4CPLUS_ERROR(kfLogger->getLogger(), content)
#define KF_LOG_INFO(kfLogger, content) LOG4CPLUS_INFO(kfLogger->getLogger(), content)
#define KF_LOG_DEBUG(kfLogger, content) LOG4CPLUS_DEBUG(kfLogger->getLogger(), content)

#define KF_LOG_FATAL_FMT(kfLogger, fmt, ...) LOG4CPLUS_FATAL_FMT(kfLogger->getLogger(), fmt, ##__VA_ARGS__)
#define KF_LOG_ERROR_FMT(kfLogger, fmt, ...) LOG4CPLUS_ERROR_FMT(kfLogger->getLogger(), fmt, ##__VA_ARGS__)
#define KF_LOG_INFO_FMT(kfLogger, fmt, ...) LOG4CPLUS_INFO_FMT(kfLogger->getLogger(), fmt, ##__VA_ARGS__)
#define KF_LOG_DEBUG_FMT(kfLogger, fmt, ...) LOG4CPLUS_DEBUG_FMT(kfLogger->getLogger(), fmt, ##__VA_ARGS__)

YJJ_NAMESPACE_START

FORWARD_DECLARE_PTR(KfLog)

class KfLog
{
protected:
    log4cplus::Logger logger;

protected:
    KfLog() {};
    KfLog(string name);

public:
    inline log4cplus::Logger& getLogger() {
        return logger;
    }

    inline void fatal(const char* content) {
        LOG4CPLUS_FATAL(logger, content);
    }

    inline void error(const char* content) {
        LOG4CPLUS_ERROR(logger, content);
    }

    inline void info(const char* content) {
        LOG4CPLUS_INFO(logger, content);
    }

    inline void debug(const char* content) {
        LOG4CPLUS_DEBUG(logger, content);
    }

    static string getConfigFolder();

    // attention: return true if really configured
    static bool doConfigure(string configureName);

    static KfLogPtr getLogger(string name);

    static KfLogPtr getStrategyLogger(string name, string log_file_name);
};

class KfLogStrategy: public KfLog
{
public:
    KfLogStrategy(string name, string log_file_name);
};

YJJ_NAMESPACE_END

#endif