#ifndef YIJINJING_DECLARE_H
#define YIJINJING_DECLARE_H

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <map>

using std::string; /**< default using string */
using std::vector  /**< default using vector */
using std::map     /**< default using map */

typedef unsigned char byte;
typedef unsigned int uint;
typedef std::pair<int, int> IntPair;

#define KUNGFU_FOLDER "/shared/kungfu/"                   /**< base folder of kungfu system */
#define KUNGFU_JOURNAL_FOLDER KUNGFU_FOLDER "journal/"    /**< where we put journal files */
#define KUNGFU_SOCKET_FOLDER KUNGFU_FOLDER "socket/"      /**< where we put socket files */
#define KUNGFU_LOG_FOLDER KUNGFU_FOLDER "log/"            /**< where we put log files */
#define PAGED_JOURNAL_FOLDER KUNGFU_JOURNAL_FOLDER "system/" /**< where we put system journal files */
#define PAGED_JOURNAL_NAME "SYSTEM"                        /**< system journal file name */

#define DECLARE_PTR(X) typedef boost::shared_ptr<X> X##Ptr /**< define smart ptr */
#define FORWARD_DECLARE_PTR(X) class X; DECLARE_PTR(X)     /**< forward defile smart ptr */
#define YJJ_NAMESPACE_START namespace kungfu {namespace yijinjing { /**< start of yjj namespace */
#define YJJ_NAMESPACE_END }};                                       /**< end of yjj namespace */
#define USING_YJJ_NAMESPACE using namespace kungfu::yijinjing;

#define JOURNAL_PREFIX string("yjj")     /**< journal file prefix */
#define JOURNAL_SUFFIX string("journal") /**< journal file suffix*/

/** fast type convert for moving address forward */
#define ADDRESS_ADD(x, delta) (void*)((uintptr_t)x + delta)

#endif // YIJINJING_DECLARE_H