#include "PageEngine.h"
#include "Page.h"
#include "Timer.h"
#include "Hash.hpp"
#include "PageUtil.h"
#include "../utils/json.hpp"

#include <sstream>
#include <mutex>
#include <signal.h>
#include <boost/bind.hpp>

USING_YJJ_NAMESPACE

using namespace boost::python;
using json = nlohmann::json;

std::mutex paged_mtx;

#define COMM_FILE KUNGFU_JOURNAL_FOLDER "PAGE_ENGINE_COMM"
const string commFileName = COMM_FILE;
const int INTERVAL_IN_MILLISEC = 1000000;

KfLogPtr static_logger;

void signal_callback(int signum)
{
    KF_LOG_INFO(static_logger, "PageEngine Caught signal: " << signum);
    exit(signum);
}

bool PageEngine::write(string  content, byte msg_type, bool is_last, short source)
{
    if (writer.get() == nullptr)
        return false;
    writer->write_frame(content.c_str(), content.length() + 1, source, msg_type, is_last, -1);
}