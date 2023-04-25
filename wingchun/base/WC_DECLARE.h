#ifndef WINGCHUN_DECLARE_H
#define WINGCHUN_DECLARE_H

#include "YJJ_DECLARE.h"
#include <thread>

typedef boost::shared_ptr<std::thread> ThreadPtr;

#define WC_NAMESPACE_START namespace kungfu {namespace wingchun {
#define WC_NAMESPACE_END }}

#define USING_WC_NAMESPACE using namespace kungfu::wingchun;

#define TICKER_MARKET_DELIMITER '@'

#define START_PYTHON_FUNC_CALLING \
    try{
#define END_PYTHON_FUNC_CALLING \
    } catch(boost::python::error_already_set &e) \
    { \
        PyErr_Print(); \
        throw std::runtime_error(__func__); \
    }

#endif // WINGCHUN_DECLARE_H