/** 
 * Page Engine, memory service of yijinjing
 * Provide centralized memory mapped file "load and lock" service
 * Enable manual controlling on the whole kungfu system via system journal
*/

#ifndef YIJINJING_PAGEENGINE_H
#define YIJINJING_PAGEENGINE_H

#include "PageCommStruct.h"
#include "KfLog.h"
#include "PageSocketHandler.h"
#include "PageServiceTask.h"
#include "JournalWriter.h"

#include <utility>
#include <thread>

YJJ_NAMESPACE_START

FORWARD_DECLARE_PTR(PstBase);
typedef boost::shared_ptr<std::thread> ThreadPtr;

/** we call each journal handler (writer or reader)
 *      -- a client for page engine.
 *  we call each "journal" linked by  client
 *      -- a user for page engine.
 *  then each writer client may only have 1 user,
 *  while each reader client may have several users.
 *  all the necessary information are stored here.
*/
struct PageClientInfo
{
    /** the index of each user linked by this client */
    vector<int> user_index_vec;
    /** register nano time */
    long reg_nano;
    /** process id */
    int pid;
    /** hash code for the client */
    int hash_code;
    /** true if this client is a writer */
    bool is_writing;
    /** true if this writer is associated with a strategy */
    bool is_strategy;
    /** start rid of the strategy (strategy only) */
    int rid_start;
    /** end rid of the strategy (strategy only) */
    int rid_end;
    /** all sources of trade engine that registered (strategy only) */
    vector<short> trade_engine_vec;
};

class PageEngine : public IPageSocketUtil
{
    friend class PstPidCheck;
    friend class PstTimeTick;
    friend class PstTempPage;
    friend class PstKfController;
private:
    // internal data structures. be careful on its thread-safety
    /** map: client -> all info (all journal usage) */
    map<string, PageClientInfo> clientJournals;
    /** map: pid -> client */
    map<int, vector<string> > pidClient;
    /** map: file attached with number of writers */
    map<PageCommMsg, int> fileWriterCounts;
    /** map: file attached with number of readers */
    map<PageCommMsg, int> fileReaderCounts;
    /** map: file to its page buffer */
    map<string, void*> fileAddrs;
    /** map: task name to task body */
    map<string, PstBasePtr> tasks;

public:
    /** default constructor */
    PageEngine();
    /** default destructor */
    ~PageEngine();

    /** start paged service, mainly start tasks */
    void start();
    /** sync stop paged service */
    void stop();

    /** set task frequency in seconds, default 1 second */
    void set_freq(double second_interval);
    /** return true if this task is inserted the first time, false if exists and updated */
    bool add_task(PstBasePtr task);
    /** return true if exists and removed */
    bool remove_task(PstBasePtr task);
    /** return true if exists and removed */
    bool remove_task_by_name(string taskName);

    /** write string constant to system journal */
    bool write(string content, byte msg_type, bool is_last=true, short source=0);
    /** return  true if msg is written in system journal */
    bool switch_trading_day();
    /** get status in python dictionary */
    boost::python::dict getStatus() const;

public:
    // functions required by IPageSocketUtil
    KfLogPtr get_logger() const { return logger; }

private:
    JournalWriterPtr writer;       /**< writer for system journal */
    KfLogPtr         logger;       /**< logger */
    void*            commBuffer;   /**< comm memory */
    string           commFile;     /**< comm file linked to memory */
    int              maxIdx;       /**< max index of current assigned comm block */
    int              microsecFreq; /**< task frequency in microseconds */
    bool             task_running; /**< task thread is running */
    bool             comm_running; /**< comm buffer checking thread is running */
    long             last_switch_nano; /**< last switch day nano time */

    /** thread for task running */
    ThreadPtr     taskThread;
    /** thread for comm buffer checking */
    ThreadPtr     commThread;
    /** thread for socket listening */
    ThreadPtr     socketThread;

private:
    // several threading to run:
    // 1. check communicate memory (main, need efficiency)
    void start_comm();
    // 2. socket listening
    void start_socket();
    // 3. run all tasks
    void start_task();

private:
    /** release the page assigned in comm msg */
    void release_page(const PageCommMsg& msg);
    /** initialize the page assigned in comm msg */
    byte initiate_page(const PageCommMsg& msg);

    /** helper functions for getStatus */
    boost::python::dict getClientInfo() const;
    boost::python::dict getPidInfo() const;
    boost::python::dict getUserInfo() const;
    boost::python::dict getFileReaderInfo() const;
    boost::python::dict getFileWriterInfo() const;
    boost::python::list getLockingFiles() const;
    boost::python::tuple getTaskInfo() const; 
};

YJJ_NAMESPACE_END

#endif