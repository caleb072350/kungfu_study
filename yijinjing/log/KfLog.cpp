#include "KfLog.h"

#include <log4cplus/initializer.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loglevel.h>

#include <sstream>
#include <fstream>
#include <unistd.h>

#define LOG_CONFIGURATION_FOLDER "/opt/kungfu/master/etc/log4cplus/"
#define LOG_CONFIGURATION_BASIC_FILENAME "default.properties"
#define LOG_CONFIGURATION_STRATEGY_PATTERN_FILENAME "strategy.pattern"
#define LOG_CONFIGURATION_BASIC_FILE LOG_CONFIGURATION_FOLDER LOG_CONFIGURATION_BASIC_FILENAME
#define LOG_CONFIGURATION_STRATEGY_PATTERN_FILE LOG_CONFIGURATION_FOLDER LOG_CONFIGURATION_STRATEGY_PATTERN_FILENAME
#define STRATEGY_LOG_FOLDER KUNGFU_LOG_FOLDER "strategy/"
#define STRATEGY_LOG_MAX_FILE_SIZE 10 * 1024 * 1024
#define STRATEGY_LOG_MAX_BACKUP_INDEX 10

USING_YJJ_NAMESPACE
using namespace log4cplus;

static bool configured = false;

bool KfLog::doConfigure(string configureName)
{
    if (!configured)
    {
        log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(configureName));
        configured = true;
        return true;
    } else {
        return false;
    }
}

KfLogPtr KfLog::getLogger(string name)
{
    return KfLogPtr(new KfLog(name));
}

KfLogPtr KfLog::getStrategyLogger(string name, string log_file_name)
{
    return KfLogPtr(new KfLogStrategy(name, log_file_name));
}

KfLog::KfLog(string name)
{
    doConfigure(LOG_CONFIGURATION_BASIC_FILE);
    logger = log4cplus::Logger::getInstance(name);
}

string KfLog::getConfigFolder()
{
    return LOG_CONFIGURATION_FOLDER;
}

KfLogStrategy::KfLogStrategy(string name, string log_file_name)
{
    if (configured)
        throw std::runtime_error("KfLogStrategy error: duplicate configuration!");
    std::stringstream ss;
    ss << STRATEGY_LOG_FOLDER << log_file_name;
    if (log_file_name.find('.') == string::npos)
        ss << ".log";
    string pattern;
    std::ifstream fin(LOG_CONFIGURATION_STRATEGY_PATTERN_FILE);
    std::getline(fin, pattern);
    // file appender
    SharedAppenderPtr fileAppender(new RollingFileAppender(ss.str(), STRATEGY_LOG_MAX_FILE_SIZE, STRATEGY_LOG_MAX_BACKUP_INDEX));
    fileAppender->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
    Logger::getRoot().addAppender(fileAppender);
    // console appender
    SharedAppenderPtr consoleAppender(new ConsoleAppender());
    consoleAppender->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
    Logger::getRoot().addAppender(consoleAppender);
    // final
    logger = Logger::getInstance(name);
    logger.setLogLevel(DEBUG_LOG_LEVEL);
    configured = true;
}

